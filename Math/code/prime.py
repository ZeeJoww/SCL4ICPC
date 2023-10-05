# reference:
# https://blog.csdn.net/apple_51931783/article/details/123937695
from random import randint
from math import gcd, isqrt


def miller_rabin(p):
    ''' 素性测试'''
    # 特判 4
    if p <= 4: return p in (2, 3)
    # 对 p-1 进行分解
    pow_2, tmp = 0, p - 1
    while tmp % 2 == 0:
        tmp //= 2
        pow_2 += 1
    # 进行多次素性测试
    for a in (2, 3, 5, 7, 11, 13, 17, 19, 23):
        basic = pow(a, tmp, p)
        # a^m 是 p 的倍数或者满足条件
        if basic in (0, 1, p - 1): continue
        # 进行 r-1 次平方
        for _ in range(1, pow_2):
            basic = basic ** 2 % p
            # 怎样平方都是 1
            if basic == 1: return False
            # 通过 a 的素性测试
            if basic == p - 1: break
        # 未通过 a 的素性测试
        if basic != p - 1: return False
    # 通过所有 a 的素性测试
    return True


def pollard_rho(n):
    ''' 求因数: 7e5 以上'''
    # 更新函数
    bias = randint(3, n - 1)
    update = lambda i: (i ** 2 + bias) % n
    # 初始值
    x = randint(0, n - 1)
    y = update(x)
    # 查找序列环
    while x != y:
        factor = gcd(abs(x - y), n)
        # gcd(|x - y|, n) 不为 1 时, 即为答案
        if factor != 1: return factor
        x = update(x)
        y = update(update(y))
    return n


class prime_factor(dict):
    ''' 质因数分解
        require: miller_rabin, pollard_rho'''

    def __init__(self, n):
        super(prime_factor, self).__init__()
        self.main(n, gain=1)

    def add(self, n, cnt):
        # 更新因数表
        self[n] = self.get(n, 0) + cnt

    def count(self, n, fac):
        # 试除并记录幂次
        cnt = 1
        n //= fac
        while n % fac == 0:
            cnt += 1
            n //= fac
        return n, cnt

    def main(self, n, gain):
        if n > 7e5:
            # 米勒罗宾判素
            if miller_rabin(n):
                self.add(n, gain)
            else:
                # pollard rho 求解因数
                fac = pollard_rho(n)
                # 求解幂次
                n, cnt = self.count(n, fac)
                # 递归求解因数的因数
                self.main(fac, gain=cnt * gain)
                # 递归求解剩余部分
                if n > 1: self.main(n, gain=gain)
        # 试除法求解
        else:
            self.try_divide(n, gain=gain)

    def try_divide(self, n, gain=1):
        ''' 试除法分解'''
        i, bound = 2, isqrt(n)
        while i <= bound:
            if n % i == 0:
                # 计数 + 整除
                n, cnt = self.count(n, i)
                # 记录幂次, 更新边界
                self.add(i, cnt * gain)
                bound = isqrt(n)
            i += 1
        if n > 1: self.add(n, gain)


def is_prime(m:int) -> bool:
    return miller_rabin(m)

n = int(input())
print(f"{n} -> {prime_factor(n)}")


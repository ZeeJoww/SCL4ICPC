#include <cstdio>
const int N = 5e6 + 7;
char s[N];

int main() {
    scanf("%s", s + 1);
    int i = 1, ans = 0;
    while (s[i]) {
        int j = i, k = i + 1;
        while (s[k] and s[j] <= s[k]) j = s[j] == s[k++] ? j + 1 : i;
        while (i <= j) i += k - j, ans ^= i - 1; // 所有右端点异或和
    }
    printf("%d\n", ans);
    return 0;
}

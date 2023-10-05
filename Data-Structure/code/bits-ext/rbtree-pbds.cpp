// 插入 xx 数
// 删除 xx 数(若有多个相同的数，因只删除一个)
// 查询 xx 数的排名(排名定义为比当前数小的数的个数 +1+1 )
// 查询排名为 xx 的数
// 求 xx 的前驱(前驱定义为小于 xx，且最大的数)
// 求 xx 的后继(后继定义为大于 xx，且最小的数)
#include <iostream>
#include <map>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using pii = pair<int, int>;
tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> T;
map<int, int> ins, era; // pbds的bbt不含重复元素，因此需要"手动支持" 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, opt, x;
    cin >> n;
    while (n--) {
        cin >> opt >> x;
        switch (opt) {
            case 1: T.insert(pii(x, ins[x]++)); break;
            case 2: T.erase(T.lower_bound(pii(x, era[x]++))); break;
            case 3: cout << T.order_of_key(pii(x, era[x])) + 1 << "\n"; break;
            case 4: cout << T.find_by_order(x - 1) -> first << "\n"; break;
            case 5: cout << (--T.lower_bound(pii(x, 0))) -> first << "\n"; break;
            case 6: cout << T.upper_bound(pii(x,ins[x])) -> first << "\n"; break;
        }
    }
    return 0;
}

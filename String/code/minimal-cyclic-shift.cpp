#include <cstdio>
const int N = 6e5 + 7;
int n, ans, s[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", s + i);
        s[i + n] = s[i];
    }
    int i = 1;
    while (i <= n) {
        int j = i, k = i + 1;
        while (k <= n * 2 && s[j] <= s[k]) j = s[j] == s[k++] ? j + 1 : i;
        while (i <= j) i += k - j, ans = i <= n ? i : ans;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d%c", s[ans - 1 + i], " \n"[i == n]);
    }
    return 0;
}

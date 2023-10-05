int count[N], sa[N];

template <typename T>
void radix_sort(const T &str, int old_rank[], int *rank, int n, int m) {
    std::fill(count, count + m + 1, 0);
    for (int i = 0; i < n; i++) {
        count[str[old_rank[i]]] ++;
    }
    for (int i = 1; i <= m; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        rank[-- count[str[old_rank[i]]]] = old_rank[i];
    }
}

void suffix_array(const std::string &str, int *sa, int n, int m) {
    static int rank[N], a[N], b[N];
    std::iota(rank, rank + n, 0);
    radix_sort(str, rank, sa, n, m);

    rank[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
        rank[sa[i]] = rank[sa[i - 1]] + (str[sa[i - 1]] != str[sa[i]]);
    }
    
    for (int h = 1; h < n; h *= 2) {
        std::iota(sa, sa + n, 0);
        for (int i = 0; i < n; i++) {
            a[i] = rank[i] + 1;
            b[i] = i + h >= n ? 0 : rank[i + h] + 1;
        }
        radix_sort(b, sa, rank, n, n);
        radix_sort(a, rank, sa, n, n);

        rank[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            rank[sa[i]] = rank[sa[i - 1]] + 
                (a[sa[i - 1]] != a[sa[i]] || b[sa[i - 1]] != b[sa[i]]);
        }
    }
}

int main() {
    std::string str;
    suffix_array(str, sa, str.size(), 128);
    for (int i = 0; i < str.size(); i++) {
        std::cout << 1 + sa[i] << " \n"[i + 1 == str.size()];
    }
}


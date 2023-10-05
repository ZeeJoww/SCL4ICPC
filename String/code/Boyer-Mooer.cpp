const int charset = 26, base = 'a', maxlen = 1e6 + 2;
int bc0[charset], *bc = bc0 - base, ss[maxlen], gs[maxlen];

void buildBC(int bc[], const std::string &p) {
    for (int j = base; j < base + charset; ++j) bc[j] = -1;
    for (int m = p.size(), j = 0; j < m; ++j) bc[int(p[j])] = j;
} // buildBC - O( s + m )

void buildSS(int ss[], const std::string &p) {
    int m = p.size();
    ss[m - 1] = m;
    for (int l = m - 1, r = m - 1,j = l - 1; j >= 0; --j)
        if (l < j && ss[m - r + j - 1] <= j - l)
            ss[j] = ss[m - r + j - 1];
        else {
            r = j, l = min(l, r);
            while (0 <= l && p[l] == p[m - r + l - 1]) --l;
            ss[j] = r - l;
        }
} // buildSS

void buildGS(int gs[], const std::string &p) {
    buildSS(ss, p);
    int m = p.size();
    for (int j = 0; j < m; ++j) gs[j] = m;
    for (int i = 0, j = m - 1; j >= 0; --j)
        if (j + 1 == ss[j])
            while (i < m - j - 1)
                gs[i++] = m - j - 1;
    for (int j = 0; j < m - 1; ++j)
        gs[m - ss[j] - 1] = m - j - 1;
} // buildGS

int match(const std::string &p, const std::string &t) {
    buildBC(bc, p), buildGS(gs, p);
    int i = 0;
    while (t.size() >= i + p.size()) {
        int j = p.size() - 1;
        while (p[j] == t[i + j]) if (0 > --j) break;
        if (0 > j) break;
        else i += max(gs[j], j - bc[int(t[i + j])]);
    }
    return i;
} // match - BM version

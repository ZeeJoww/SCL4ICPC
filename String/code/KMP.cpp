// optimize = false -> next = \pi
std::vector<int> get_next(const std::string &t, bool optimize) {
    std::vector<int> next(t.size());
    int i = 0, j = -1;
    next[i] = j;
    while (t[i] != '\0') {
        if (j == -1 || t[i] == t[j]) {
            i++, j++;
            if (optimize && t[i] == t[j]) next[i] = next[j]; 
            else next[i] = j;
        }
        else j = next[j];
    }
    return next;
}
std::vector<int> kmp(const std::vector<int> &next, const std::string &s, const std::string &t) {
    std::vector<int> pos;
    int i = 0, j = 0;
    while (s[i] != '\0') {
        if (j == -1 || s[i] == t[j]) i++, j++;
        else j = next[j];
        if (j > -1 && t[j] == '\0') pos.push_back(i - j + 1), j = next[j];
    }
    return pos;
}

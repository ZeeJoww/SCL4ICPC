struct cmp { bool operator() (int a, int b) { return a > b; } };
priority_queue<int, vector<int>, cmp> pque;
auto cmp = [](int x, int y) { return x > y; };
priority_queue<int, vector<int>, decltype(cmp) > pque1(cmp);

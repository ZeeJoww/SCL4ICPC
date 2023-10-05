convex get_convex(convex p) {
    std::sort(p.begin(), p.end(), [&] (point a, point b) -> bool {
        return a.y != b.y ? a.y < b.y : a.x < b.x;
    });
    int n = (int) p.size(), tp = 0, lim = 1;
    std::vector<int> used(n, 0), t(2 * n);
    for (int i = 0; i < n; i++) {
        while (tp > lim and cross(p[t[tp - 1]] - p[t[tp - 2]], p[i] - p[t[tp - 2]]) <= 0) {
            used[t[-- tp]] = 0;
        }
        used[t[tp ++] = i] = 1;
    }
    lim = std::max(lim, tp);
    for (int i = n - 2; i >= 0; i--) {
        if (used[i]) continue;
        while (tp > lim and cross(p[t[tp - 1]] - p[t[tp - 2]], p[i] - p[t[tp - 2]]) <= 0) {
            used[t[-- tp]] = 0;
        }
        used[t[tp ++] = i] = 1;
    }
    while (cross(p[t[tp - 1]] - p[t[tp - 2]], p[t[0]] - p[t[tp - 2]]) <= 0) {
        used[t[-- tp]] = 0;
    }
    convex c(tp);
    for (int i = 0; i < tp; i++) {
        c[i] = p[t[i]];
    }
    return c;
}


void reorder_convex(convex &c) {
    int p = 0;
    for (int i = 1; i < (int) c.size(); i++) {
        if (c[i].y < c[p].y or (c[i].y == c[p].y and c[i].x < c[p].x)) {
            p = i;
        }
    }
    std::rotate(c.begin(), c.begin() + p, c.end());
}

convex minkowski_sum(convex c1, convex c2) {
    auto prepare = [&] (convex &c) {
        reorder_convex(c);
        c.push_back(c[0]);
        c.push_back(c[1]);
    };
    int n1 = (int) c1.size(), n2 = (int) c2.size();
    prepare(c1);
    prepare(c2);
    convex c;
    for (int i = 0, j = 0; i < n1 or j < n2; ) {
        c.push_back(c1[i] + c2[j]);
        auto value = cross(c1[i + 1] - c1[i], c2[j + 1] - c2[j]);
        if (value >= 0 and i < n1) i++;
        if (value <= 0 and j < n2) j++;
    }
    return c;
}

bool in_convex(point p, const convex &c) {
    int lo = 0, hi = (int) c.size() - 1;
    while (lo < hi) {
        int mi = hi - (hi - lo) / 2;
        if (cross(c[mi] - c[0], p - c[0]) >= 0) {
            lo = mi;
        } else {
            hi = mi - 1;
        }
    }
    if (hi == 0) {
        return false;
    } else if (hi == (int) c.size() - 1) {
        return on_segment(p, c[0], c[hi]);
    } else {
        return in_triangle(p, c[0], c[hi], c[hi + 1]); 
    }
}



// required: P <- getConvexHull(P); 
double findConvexHullWidth(const std::vector<point> &P) {
    double res = inf;
    int sz = P.size();
    for (int i = 0, q = 1; i < sz; ++i) {
        int j = (i + 1) % sz;
        while (cross(P[j] - P[i], P[q] - P[i]) < cross(P[j] - P[i], P[(q + 1) % sz] - P[i])) {
            q = (q + 1) % sz;
        }
        res = std::min(res, DistLinePoint(P[i], P[j], P[q]));
    }
    return res;
}

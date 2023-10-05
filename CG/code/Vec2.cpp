point rotate(point p, double a) {
    double cosa = std::cos(a), sina = std::sin(a);
    return point(p.x * cost - p.y * sint, p.x * sint + p.y * cost);
}


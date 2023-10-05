// https://fanfansann.blog.csdn.net/article/details/108834399
Circle GetCircumcircle(Point p1, Point p2, Point p3) {
    double Bx = p2.x-p1.x, By = p2.y-p1.y;
    double Cx = p3.x-p1.x, Cy = p3.y-p1.y;
    double D = 2*(Bx*Cy-By*Cx);
    double ansx = (Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D + p1.x;
    double ansy = (Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D + p1.y;
    Point p(ansx, ansy);
    return Circle(p, Length(p1-p));
}

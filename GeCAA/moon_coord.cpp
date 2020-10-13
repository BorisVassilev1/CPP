#include <iostream>
#include <math.h>
using namespace std;

class Vector2d {
public:
    double x;
    double y;

    Vector2d(double x = 0, double y = 0) : x(x), y (y) {}

    Vector2d(double x1, double x2, double x3, double y1, double y2, double y3) {
        x = x1 + x1 / 60. + x3 / 3600.;
        y = y1 + y2 / 60. + y3 / 3600.;
    }

    Vector2d operator +(const Vector2d& other) {
        Vector2d result(x + other.x, y + other.y);
        return result;
    }

    Vector2d operator -(const Vector2d& other) {
        Vector2d result(x - other.x, y - other.y);
        return result;
    }

    Vector2d operator *(const Vector2d& other) {
        Vector2d result(x * other.x, y * other.y);
        return result;
    }

    Vector2d operator /(const Vector2d& other) {
        Vector2d result(x / other.x, y / other.y);
        return result;
    }

    double length() {
        return sqrt(x * x + y * y);
    }
};
ostream& operator<<(ostream& os, const Vector2d& v)
{
    os << '(' << v.x << ' ' << v.y << ')';
    return os;
}
/* 5
paab(223 + 59 / 60. + 55.8 / 3600., 57 + 19 / 60. + 29.9 / 3600.),
paac(248 + 42 / 60. + 07.8 / 3600., 55 + 42 / 60. + 25.9 / 3600.),

4
paab(223 + 37 / 60. + 15.8 / 3600., 57 + 27 / 60. + 09.1 / 3600.),
paac(248 + 25 / 60. + 59.6 / 3600., 55 + 52 / 60. + 43.4 / 3600.),

*/

int main() {

    Vector2d paab(223 + 59 / 60. + 55.8 / 3600., 57 + 19 / 60. + 29.9 / 3600.),
            paac(248 + 42 / 60. + 07.8 / 3600., 55 + 42 / 60. + 25.9 / 3600.),
            pam(0,0),
            pbab(1163 , 879),
            pbac(2058 , 1029),
            pbm(1753 , 1328),

            paac1 = paac - paab,
            pam1 = pam - paab,

            pbac1 = pbac - pbab,
            pbm1 = pbm - pbab,

            x = paac1 / pbac1;
    pam1 = x * pbm1;
    pam = pam1 + paab;
    cout << pam << endl;

    /*Vector2d real_1(),
    real0(239.13636, 52.28933),
            real1(239.423, 52.13605),
            real2(239.708, 51.98236),
            real3(239.99136,51.82819);*/

    Vector2d
            real_6(237 + 22 / 60. + 50.2 / 3600., 53 + 11 / 60. + 56.0 / 3600.),
            real_5(237 + 40 / 60. + 39.2 / 3600., 53 + 2 / 60. + 54.7 / 3600.),
            real_4(237 + 58 / 60. + 22.0 / 3600., 52 + 53 / 60. + 51.5 / 3600.),
            real_3(238 + 15 / 60. + 58.4 / 3600., 52 + 44 / 60. + 46.6 / 3600.),
            real_2(238 + 33 / 60. + 28.7 / 3600., 52 + 35 / 60. + 40.0 / 3600.),
            real_1(238 + 50 / 60. + 52.8 / 3600., 52 + 26 / 60. + 31.6 / 3600.),
            real0(239 + 8 / 60. + 10.9 / 3600., 52 + 17 / 60. + 21.6 / 3600.),
            real1(239 + 25 / 60. + 22.8 / 3600., 52 + 8 / 60. + 09.8 / 3600.),
            real2(239 + 42 / 60. + 28.8 / 3600., 51 + 58 / 60. + 56.5 / 3600.),
            real3(239 + 59 / 60. + 28.9 / 3600., 51 + 49 / 60. + 41.5 / 3600.),
            real4(240 + 16 / 60. + 23.0 / 3600., 51 + 40 / 60. + 25.0 / 3600.),
            real5(240 + 33 / 60. + 11.4 / 3600., 51 + 31 / 60. + 06.8 / 3600.);

    Vector2d real = real5;
    Vector2d diff = (pam - real);
    cout << real << endl;
    cout << diff << " " << diff.length();

}

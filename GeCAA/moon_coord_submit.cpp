#include <iostream>
#include <math.h>
using namespace std;

class Vector2d {
public:
    double x;
    double y;

    Vector2d(double x = 0, double y = 0) : x(x), y (y) {}

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

int main() {

    Vector2d paab(223 + 59 / 60. + 55.8 / 3600., 57 + 19 / 60. + 29.9 / 3600.),
            paac(248 + 42 / 60. + 07.8 / 3600., 55 + 42 / 60. + 25.9 / 3600.),
            pam(0,0),
            pbab(1161 , 879),
            pbac(2058 , 1029),
            pbm(1759 , 1326),

            paac1 = paac - paab,
            pam1 = pam - paab,

            pbac1 = pbac - pbab,
            pbm1 = pbm - pbab,

            x = paac1 / pbac1;
    pam1 = x * pbm1;
    pam = pam1 + paab;
    cout << pam << endl;
}

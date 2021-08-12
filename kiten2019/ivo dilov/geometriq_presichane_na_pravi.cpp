#include <iostream>
#include <cmath>
using namespace std;

struct Vector2 {
    double x;
    double y;
    Vector2 (double x, double y) : x(x), y(y) {}
    Vector2 add(Vector2 &a) {
        Vector2 c(x - a.x,y - a.y);
        return c;
    }
    Vector2 sub(Vector2 &a) {
        Vector2 c(x - a.x,y - a.y);
        return c;
    }
    Vector2 mult(double a) {
        Vector2 c(x * a, y * a);
        return c;
    }
    double orientedFace(Vector2 &ab, Vector2 &ac) const {
        double ans = (ab.x * ac.y - ac.x * ab.y);
        return ans;
    }
    void operator =(const Vector2 &a) {
        x = a.x;
        y = a.y;
    }
    double length() {
        return sqrt(this->x * this->x + this->y * this->y);
    }
    Vector2 normalized() {
        return (mult(1/this->length()));
    }
};


int main() {
    Vector2 a(0,0);
    Vector2 b(0,0);
    Vector2 c(0,0);
    Vector2 d(0,0);

    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

    double A1 = b.y - a.y;
    double B1 = a.x - b.x;
    double C1 = a.x * b.y - b.x * a.y;

    double A2 = d.y - c.y;
    double B2 = c.x - d.x;
    double C2 = c.x * d.y - d.x * c.y;


    double x = -(C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
    double y = -(C2 * A1 - C1 * A2) / (B1 * A2 - B2 * A1);

    cout << x << " " << y;
}

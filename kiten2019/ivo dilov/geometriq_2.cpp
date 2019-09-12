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

    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

    Vector2 ab = b.sub(a);
    Vector2 ac = c.sub(a);
    ab = ab.normalized();

    cout << abs(a.orientedFace(ab,ac));
}

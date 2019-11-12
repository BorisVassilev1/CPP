#include <iostream>
#include <set>

using namespace std;

struct Line {
    double a = 0, b = 0;
    Line(double a, double b) : a(a), b(b){}

    mutable double intersectRightX;

    float result(double x) {
        return this->a * x + this-> b;
    }

    bool operator < (const Line &other) const {
        return this->a < other.a;
    }

    bool operator < (const double x) const{
        return this->intersectRightX < x;
    }

};

multiset<Line> upper_envelope;

int main() { ///LAINA:
    upper_envelope.insert(Line(-1, 5));
    //upper_envelope.insert(Line( 0, 3));
    upper_envelope.insert(Line(2, -5));
    auto a = upper_envelope.upper_bound(Line(0, 3));
    cout << a->a << " " << a->b;
}

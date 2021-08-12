#include <iostream>
#include <cmath>
using namespace std;

int sign(double a) {if(a > 0) {return 1;} else if(a == 0) {return 0;} else {return -1;}}

struct Vector2 {
    double x;
    double y;
    Vector2 (double x, double y) : x(x), y(y) {}
    Vector2 add(Vector2 &a) {
        x += a.x;
        y += a.y;
    }
    Vector2 sub(Vector2 &a) {
        x -= a.x;
        y -= a.y;
    }
    double orientedFace(Vector2 &a, Vector2 &b, Vector2 &c) const {
        Vector2 ab = b.sub(a);
        Vector2 ac = c.sub(a);
        double ans = (ab.x * ac.y - ac.x * ab.y);
        return ans;
    }
};

int main() {
    int n;
    cin >> n;
    Vector2 prevPoint(0,0);
    Vector2 point(0,0);
    cin >> point.x >> point.y;
    cin >> prevPoint.x >> prevPoint.y;
    int firstSign = 0;
    for(int i = 1; i < n; ++ i) {
        Vector2 currPoint(0,0);
        cin >> currPoint.x >> currPoint.y;
        double face = point.orientedFace(point, prevPoint, currPoint);
        if(i == 0) {if(sign(face) == 0) {cout << "ne";} else {firstSign = sign(face);}}
        else if( face == 0 || firstSign != sign(face)) {
                cout << "ne";
            return 0;
        }
        cout << (face == 0);
    }
    //cout << firstSign;
    cout << "da";
}
/*
4
-1 0

0 0
0 4
4 4
4 0
*/

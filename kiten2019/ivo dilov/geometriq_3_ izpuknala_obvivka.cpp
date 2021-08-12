#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct Vector2 {
    double x = 0;
    double y = 0;
    Vector2 (double x, double y) : x(x), y(y) {}
    Vector2 () : x(0), y(0) {}
    Vector2 operator +(const Vector2 a) const {
        Vector2 c(x + a.x,y + a.y);
        return c;
    }
    Vector2 operator -(const Vector2 a) const {
        Vector2 c(x - a.x,y - a.y);
        return c;
    }
    Vector2 operator *(const double a) const {
        Vector2 c(x * a, y * a);
        return c;
    }
    Vector2 operator /(const double a) const  {
        Vector2 c(x / a, y / a);
        return c;
    }
    double operator *(const Vector2 ac) const {
        double ans = (x * ac.y - ac.x * y);
        return ans;
    }
    void operator =(const Vector2 a) {
        x = a.x;
        y = a.y;
    }
    double length() {
        return sqrt(x * x + y * y);
    }
    double lengthSquared() {
        return x * x + y * y;
    }
    Vector2 normalized() {
        return  (*this)/ length();
    }
    Vector2 operator += (const Vector2 a) {
        (*this) = (*this) - a;
        return *this;
    }
    Vector2 operator -= (const Vector2 a) {
        (*this) = (*this) - a;
        return *this;
    }
    Vector2 operator *= (const double a) {
        (*this) = (*this) * a;
        return *this;
    }
    Vector2 operator /= (const double a) {
        (*this) = (*this) / a;
    }
    bool operator == (const Vector2 a) const {
        return x == a.x && y == a.y;
    }
    bool operator != (const Vector2 a) const {
        return x != a.x || y != a.y;
    }
};

Vector2 points[100];
Vector2 first;
vector<Vector2> hull;

bool compare(Vector2 a, Vector2 b) {
    if(a == first) return true;
    if(b == first) return false;
    double x =  (a - first) * (b - first);
    if(x != 0) return x < 0;
    else {return a.lengthSquared() > b.lengthSquared();}
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        cin >> points[i].x >> points[i].y;
    }
    first = points[0];

    for(int i = 1; i < n; ++ i) {
        if(points[i].y < first.y) {
            first = points[i];
        }
    }

    hull.push_back(first);
    sort(points , points + n, compare);
    hull.push_back(points[1]);
    cout << endl;
    for( int i = 0; i < n; i ++) {
        cout << points[i].x << " " << points[i].y << endl;
    }

    cout << endl;
    for(int i = 2; i < n; i ++) {
        Vector2 candidate = points[i];
        //cout << hull[hull.size() - 2].x;
        while((candidate - hull.back()) * (candidate - hull[hull.size() - 2]) < 0) {
            hull.pop_back();
        }
        hull.push_back(candidate);
    }
    for(Vector2 a : hull)
        cout << a.x << " " << a.y << endl;
}

/*
7
0 0
-2 3
-8 3
-5 -5
4 -2
3 3
4 7


*/

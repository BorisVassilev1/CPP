#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

///DA PITAM STANISLAV!!!! ILI DA DEBUGVAM!
///USLOVIE: 7.pdf

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
    friend ostream& operator << (ostream& out, Vector2 a){
        return out<<"("<<a.x<<", "<<a.y<<")";
    }
};

Vector2 points[1000];
int n;

double longestDist(double pos) {
    Vector2 point(pos, 0);
    double longestDistance = -1;
    for(int j = 0; j < n; j ++) {
        float dist = (points[j] - point).lengthSquared();
        if(dist > longestDistance) {
            longestDistance = dist;
        }
    }
    return longestDistance;
}

bool comp(Vector2 &a, Vector2 &b) {
    return a.x < b.x;
}

int main() {
    cout << fixed << setprecision(10) << endl;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points, points + n, comp);
    for(int i = 0; i < n; i ++) {
        cout << points[i] << " ";
    }
    cout << endl;
    double wall1 = points[0].x - 1, wall2 = points[n - 1].x + 1;
    double point1 = wall1 * 2.0 / 3.0 + wall2 / 3.0, point2 = wall1 / 3.0 + wall2 * 2.0 / 3.0;
    //cout << point1 << " " << point2 << " ";
    ///tozi trenary search ne raboti :(
    for(int i = 0; i < 40; ++ i) {
        double dist1 = longestDist(point1);
        double dist2 = longestDist(point2);

        if(dist1 < dist2) {
            wall2 = point2;
            point1 = wall1 * 2.0 / 3.0 + wall2 / 3.0;
            point2 = wall1 / 3.0 + wall2 * 2.0 / 3.0;
        }
        else {
            wall1 = point1;
            point1 = wall1 * 2.0 / 3.0 + wall2 / 3.0;
            point2 = wall1 / 3.0 + wall2 * 2.0 / 3.0;
        }
        //cout << dist1 << " " << dist2 << endl;
        cout << point1 << " " << point2 << " " << (dist1 < dist2) << endl;
    }
    cout << point1 << " " << point2;
}

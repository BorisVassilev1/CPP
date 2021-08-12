#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

///OOF TVA NE RABOTI TR DA SE OPRAVI

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


Vector2 a[1000];
vector<Vector2> hull;
pair<Vector2, Vector2> kur[10000];

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        cin >> a[i].x >> a[i].y;
    }
    if(a[0].y > a[1].y)   hull.push_back(a[0]);
    hull.push_back(a[1]);
    kur[1].first = a[0];
    kur[n - 2].second = a[n - 1];///dobavi 2 kum otgovora
    for(int i = 2; i < n; ++ i) {
        Vector2 candidate = a[i];
        while(hull.size() != 0 && (candidate - hull.back()) * (candidate - hull[hull.size() - 2]) > 0) {cout << hull.back(); hull.pop_back();}
        kur[i].first = hull[hull.size() - 1];
        hull.push_back(candidate);
    }
    cout << endl;
    hull.clear();
    for(int i = n - 1; i >= 2; -- i) {
        Vector2 candidate = a[i];
        while(hull.size() != 0 && (candidate - hull.back()) * (candidate - hull[hull.size() - 2]) < 0) {hull.pop_back();}
        kur[i].second = hull[hull.size() - 1];
        hull.push_back(candidate);
    }

    for(int i = 0; i < n; ++ i) {
        cout << a[i] << kur[i].first << endl;
    }
}
/*
9
1 1
2 2
3 7
4 4
6 3
7 3
8 5
9 3
10 4
*/

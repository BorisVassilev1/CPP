#include <iostream>
#include <math.h>

class vec2 {
public:
    double x = 0, y = 0;
    
    vec2() : x(0), y(0) {}

    vec2(double x, double y) : x(x), y(y) {}

    double length() {
        return sqrt(length_squared());
    }
    
    double length_squared() {
        return x * x + y * y;
    }

    vec2& normalize() {
        (*this) *= 1.0 / length();
        return *this;
    }

    vec2 operator + (const vec2& other)  const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator += (const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2 operator - (const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }
    
    vec2 operator - () const {
        return vec2(-x, -y);
    }

    vec2& operator -= (const vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    vec2 operator * (double scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    vec2& operator *= (double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    vec2 operator / (double scalar) const {
        return vec2(x / scalar, y / scalar);
    }

    vec2& operator /= (double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    
    bool operator == (const vec2& other) const{
        double eps = 0.000001;
        return (abs(x - other.x) < eps) && (abs(y - other.y) < eps);
    }

    friend std::ostream& operator << (std::ostream& out, const vec2& v) {
        return out << "vec2 [x: " << v.x << ", y: " << v.y << "]";
    }

    friend std::istream& operator >> (std::istream& in, vec2& v) {
        return in >> v.x >> v.y;
    }
};

double dot(const vec2& a, const vec2& b) {
    return a.x * b.x + a.y * b.y;
}

vec2 reflect(const vec2& I, const vec2& N) {
    return I - N * 2.0 * dot(N, I);
}

double heron(double ab, double bc, double ca) {
    double p = (ab + bc + ca) / 2.0;
    return sqrt(p * (p - ab) * (p - bc) * (p - ca));
}

class Board {
public:
    vec2 a, b, c, d;

    Board(const vec2& a, const vec2& b, const vec2& c, const vec2& d) : a(a), b(b), c(c), d(d) {}

    Board(const vec2& a, const vec2& c) : Board(a, vec2(c.x, a.y), c, vec2(a.x, c.y)) {}
    
    vec2 globalToBoard(const vec2& p) {
        vec2 size = getSize();
        double ap = (p - a).length();
        double bp = (p - b).length();
        double dp = (p - d).length();
        
        double y = heron(ap, bp, size.x) * 2.0f / size.x;
        double x = heron(ap, dp, size.y) * 2.0f / size.y;
        
        return vec2(x,y);
    }

    vec2 boardToGlobal(const vec2& p) {
        vec2 size = getSize();
        return a + (b - a) * p.x / size.x + (d - a) * p.y / size.y;
    }

    const vec2 getSize() {
        float x = (b - a).length();
        float y = (d - a).length();
        return vec2(x, y);
    }
};

struct HitInfo {
    double dist;
    vec2 position;
    vec2 normal;

    friend std::ostream& operator << (std::ostream& out, const HitInfo& hit) {
        return out << "HitInfo: [dist: " << hit.dist << ", position: " << hit.position << ", normal: " << hit.normal << "]";
    }
};

class AABB {
public:
    vec2 min;
    vec2 max;

    AABB(const vec2& min, const vec2& max) : min(min), max(max) {}
    
    AABB(const vec2& size) : min(0,0), max(size) {}

    void intersect(const vec2& origin, const vec2& direction, const double r, HitInfo& hit) {
        double t1 = (min.x + r - origin.x) / direction.x;
        double t2 = (max.x - r - origin.x) / direction.x;
        double t3 = (min.y + r - origin.y) / direction.y;
        double t4 = (max.y - r - origin.y) / direction.y; 

        double t = 2e9;
        vec2 normal;
        if(t1 > 0 && t1 < t) {
            t = t1;
            normal = vec2(1, 0);
        }
        if(t2 > 0 && t2 < t) {
            t = t2;
            normal = vec2(-1, 0);
        }
        if(t3 > 0 && t3 < t) {
            t = t3;
            normal = vec2(0, 1);
        }
        if(t4 > 0 && t4 < t) {
            t = t4;
            normal = vec2(0, -1);
        }
        
        hit.dist = t;
        hit.position = origin + direction * t;
        hit.normal = normal; 
    }

    bool isOnVertex(const vec2 ball, const double r) {
        return (ball == max + vec2(-r, -r) ||
                ball == min + vec2( r,  r) ||
                ball == vec2(min.x + r, max.y - r) || 
                ball == vec2(max.x - r, min.y + r));
    }
};

int main() {
    Board board(vec2(20, 10), vec2(120, 110), vec2(70, 160), vec2(-30, 60));
    //Board board(vec2(0,0),vec2(320, 160));

    const double r = 1.;

    vec2 board_size = board.getSize();

    AABB box(board_size);
     
    vec2 ball, dir;
    double power;
    std::cin >> ball >> dir >> power;
    
    double distance = dir.length() * power;
    dir.normalize();
    
    vec2 target = ball + dir;
    target = board.globalToBoard(target);
    ball = board.globalToBoard(ball);
    dir = target - ball;
    while(694201337) { 
        HitInfo hit;
        box.intersect(ball, dir, r, hit);
        
        if(hit.dist > distance) {
            std::cout << board.boardToGlobal(ball + dir * distance) << std::endl;
            break;
        } else {
            if(box.isOnVertex(ball, r)) 
                std::cout << board.boardToGlobal(hit.position) << std::endl;
            distance -= hit.dist;
            std::cout << "the ball hit the table at: " << board.boardToGlobal(hit.position) << std::endl;
            ball = hit.position;
            dir = reflect(dir, hit.normal);
        }
    }
}




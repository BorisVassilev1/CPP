#include <iostream>
#include <math.h>

class vector2d {
	public:
	double x, y;

	vector2d() : x(0), y(0) {}

	vector2d(double x, double y) : x(x), y(y) {}

	vector2d operator + (const vector2d &other) const {
		return vector2d(x + other.x, y + other.y);
	}
	
	vector2d & operator += (const vector2d &other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	vector2d operator - (const vector2d &other) const {
		return vector2d(x - other.x, y - other.y);
	}

	vector2d & operator -= (const vector2d &other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	
	vector2d operator * (const double num) const {
		return vector2d(x * num, y * num);
	}

	vector2d & operator *= (const double num) {
		x *= num;
		y *= num;
		return *this;
	}

	vector2d operator / (const double num) const {
		return vector2d(x / num, y / num);
	}

	vector2d & operator /= (const double num) {
		x /= num;
		y /= num;
		return *this;
	}
	
	static double dot(const vector2d &a, const vector2d &b) {
		return a.x * b.x + a.y * b.y;
	}
	
	double dot (const vector2d& other) const {
		return x * other.x + y * other.y;	
	}
	
	static vector2d lerp(const vector2d &a, const vector2d &b, const double x) {
		return a * x + b * (1-x);
	}
	
	double length_squared() const{
		return dot(*this);
	}

	double length() const {
		return sqrt(length_squared());
	}

	vector2d &normalize() {
		*this /= length();
		return *this;
	}

	friend std::ostream& operator << (std::ostream &out, vector2d v) {
		return out << "(" << v.x << " " << v.y << ")";
	}

	friend std::istream& operator >> (std::istream &in, vector2d &v) {
		return in >> v.x >> v.y;
	}
};

class vector3d {
	public:
	double x, y, z;

	vector3d() : x(0), y(0), z(0) {}

	vector3d(double x, double y, double z) : x(x), y(y), z(z) {}

	vector3d operator + (const vector3d &other) const {
		return vector3d(x + other.x, y + other.y, z + other.z);
	}
	
	vector3d & operator += (const vector3d &other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vector3d operator - (const vector3d &other) const {
		return vector3d(x - other.x, y - other.y, z - other.z);
	}

	vector3d & operator -= (const vector3d &other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	
	vector3d operator * (const double num) const {
		return vector3d(x * num, y * num, z * num);
	}

	vector3d & operator *= (const double num) {
		x *= num;
		y *= num;
		z *= num;
		return *this;
	}

	vector3d operator / (const double num) const {
		return vector3d(x / num, y / num, z / num);
	}

	vector3d & operator /= (const double num) {
		x /= num;
		y /= num;
		z /= num;
		return *this;
	}
	
	static double dot(const vector3d &a, const vector3d &b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
		
	double dot (const vector3d& other) const {
		return x * other.x + y * other.y + z * other.z;	
	}

	static vector3d cross(const vector3d &a, const vector3d &b) {
		vector3d res(
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
				);
		return res;
	}
	
	vector3d cross(const vector3d &b) {
		return vector3d(
				y * b.z - z * b.y,
				z * b.x - x * b.z,
				x * b.y - y * b.x
				);
 
	}

	static vector3d lerp(const vector3d &a, const vector3d &b, const double x) {
		return a * x + b * (1-x);
	}

	double length_squared() const{
		return dot(*this);
	}

	double length() const {
		return sqrt(length_squared());
	}
	
	vector3d &normalize() {
		*this /= length();
		return *this;
	}

	friend std::ostream& operator << (std::ostream &out, vector3d v) {
		return out << "(" << v.x << " " << v.y << " " << v.z << ")";
	}

	friend std::istream& operator >> (std::istream &in, vector3d &v) {
		return in >> v.x >> v.y >> v.z;
	}
};


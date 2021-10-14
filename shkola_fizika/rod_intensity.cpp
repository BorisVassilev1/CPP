#include <iostream>
#include "vectors.cpp"

using namespace std;

#define k 9e9

const double rod_length = .1;
const int points_count = 10;
const double charge = 1e-9;
vector2d point(0, 0.1);

vector2d intensity(vector2d& charge_pos, double charge, vector2d& point) {
	double d_sq = (point - charge_pos).length_squared();
	vector2d dir = (point - charge_pos).normalize();
	double mag = k * (charge / d_sq);
	return dir * mag;
}

vector2d eval_intensity() {
	double point_charge = charge / points_count;
	vector2d rod_start(- rod_length / 2, 0), rod_end( rod_length / 2, 0);
	
	vector2d result;

	for(int i = 0; i < points_count; i ++) {
		double ratio = (double(i) + 0.5) / points_count;
		vector2d pos = vector2d::lerp(rod_start, rod_end, ratio);
		vector2d point_intensity = intensity(pos, point_charge, point);	
		//cout << pos << endl << point_intensity << endl;
		result += point_intensity;
	}
	return result;
}

int main() {
	vector2d num = eval_intensity();
	double integral = double(k) * charge / point.y / sqrt(point.y * point.y + rod_length * rod_length / 4);
	double mistake = (num.y - integral) / integral;
	cout << "result: " << num << " mistake: " << mistake << endl;	
}

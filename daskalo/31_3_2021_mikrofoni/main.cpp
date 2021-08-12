#include <iostream>
#include <algorithm>
using namespace std;

struct human {
	int arrival_time = -1;
	int present_time = -1;

	human() {};
	human(int a, int b) {
		arrival_time = a;
		present_time = b;
	}

	bool operator < (human& other) {
		if(arrival_time != other.arrival_time)
			return arrival_time < other.arrival_time;
		else
			return present_time > other.present_time;
	}
};

int n, m;

human speakers[10010];

int microphones[10010];

int wait_time(int speaker, int microphone) {
	int time = - speakers[speaker].arrival_time + microphones[microphone];
	return time > 0 ? time : 0;
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < m; i ++) {
		int arr, pres;
		cin >> arr >> pres;
		speakers[i] = human(arr, pres);
	}

	sort(speakers, speakers + m);

	for(int i = 0; i < m; i ++) {
		//cout << endl << speakers[i].arrival_time << " " << speakers[i].present_time << endl;
		
		int min_time = 1e5;
		int min_index = -1;
		for(int j = 0; j < n; j ++) {
			int time = wait_time(i, j);
			if(time < min_time) {
				min_time = time;
				min_index = j;
			}
		}
		//cout << min_index << " " << min_time << " " << microphones[min_index] << endl;
		microphones[min_index] = speakers[i].arrival_time;
		microphones[min_index] += speakers[i].present_time;
		//cout << microphones[min_index] << endl;
	}

	int max_time = 0;
	int max_index = -1;
	for(int i = 0; i < m; i ++) {
		if(microphones[i] >= max_time) {
			max_time = microphones[i];
			max_index = i;
		}
	}
	cout << max_time << " " << max_index + 1 << endl;
}

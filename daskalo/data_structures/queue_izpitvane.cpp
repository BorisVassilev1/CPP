#include <iostream>
#include "queue.cpp"
#include <algorithm>
using namespace std;

struct client {
    int arrival_time;
    int examination_time;

    client() : arrival_time(0), examination_time(0) {}
    client(int arrival_time, int examination_time) : arrival_time(arrival_time), examination_time(examination_time) {}

    const bool operator < (const client& other) {
        return arrival_time < other.arrival_time;
    }

    void operator =(const client& other) {
        arrival_time = other.arrival_time;
        examination_time = other.examination_time;
    }

    friend istream& operator >> (istream& in, client& c) {
        return (in >> c.arrival_time >> c.examination_time);
    }
 };

int n = 0;
client arr[1000];

int main() {

    client curr;
    for(; cin >> curr; n++) {
        arr[n] = curr;
    }

    sort(arr, arr + n);

    queue<client> q;
    for(int i = 0; i < n; i ++) {
        q.push(arr[i]);
    }

    int time_passed = 0;

    while(!q.empty()) {
        client& c = q.front();
        if(time_passed < c.arrival_time)
            time_passed = c.arrival_time;
        time_passed += c.examination_time;
        q.pop();
    }
    cout << time_passed - arr[n-1].arrival_time;
}

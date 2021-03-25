#include <iostream>
#include <math.h>
#include "queue.cpp"


using namespace std;

int main() {
    queue<int> q;

    int machines_a,
        machines_b,
        time_a,
        time_b,
        time_pack,
        size_a,
        size_b;

    cin >> machines_a >>
        machines_b >>
        time_a >>
        time_b >>
        time_pack >>
        size_a >>
        size_b;

    double prod_timer_a = time_a;
    double prod_timer_b = time_b;

    double prod_period_a = time_a / (float)machines_a;
    double prod_period_b = time_b / (float)machines_b;

    double pack_timer = time_pack;

    do {
        if(pack_timer <= prod_timer_a && pack_timer <= prod_timer_b) {
        
        }
        if(prod_timer_a <= prod_timer_b && prod_timer_a <= pack_timer) {
            
        } 
        // oh fuk

    } while(!q.empty());
}

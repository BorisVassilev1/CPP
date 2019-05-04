#include <iostream>

using namespace std;

int ans[100000];

int main() {
    int N;
    cin >> N;

    int current = 0;
    int largest = 0;
    int last = -1;
    for(int i = 0; i < N; i ++)
    {
        int number;
        cin >> number;
        if(number < last)
        {
            current ++;
            for(int j = i + 1; j > i - current - 1; j --)
            {
                //cout << "increasing " << j;
                ans[j] ++;
            }
        }
        else
        {
            if(largest < current)
            {
                largest = current;
            }
        }
        last = number;
    }
    for(int i = 0; i < N; i ++)
    {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}

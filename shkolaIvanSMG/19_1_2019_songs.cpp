#include <iostream>
using namespace std;
const int MAX_N = 50000;
int n;
int numbers1[MAX_N];
int numbers2[MAX_N];

int position[MAX_N];
int main()
{
    cin >> n;
    for(int i = 0; i < n; i ++)
    {   int x;
        cin >> x;
        --x;
        position[x] = i;
    }
    for(int i = 0; i < n; i ++)
    {
        int x;
        cin >> x;
        --x;
        numbers2[i] = position[x];
    }
    for(int i = 0; i < n; i ++)
    {
        cout << numbers2[i] + 1 << " ";
    }
}

#include <iostream>
using namespace std;

const int MAX_K = 100000;
const int MAX_N = 100000;
int sheep[MAX_N];
int cots[MAX_K];

bool CanBeDoneWith(int m)
{
    int lastCotSheeps = 0;
    int currentCot = 0;
    int currSheep = 0;
    while(true)
    {
        if(abs(sheeps[currSheep] - cots[currentCot]) < m)
        {
            ++lastCotSheeps;
            if(lastCotSheeps == k)
            {
                ++currentCot;
            }
        }
        else{
            ++currentCot;
        }
    }
}

int binarysearch()
{
    int l = 0, r = n;
    while(l < r - 1)
    {
        int m = (l + r) / 2;
        if(canBeDoneWith(m))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    return r;
}

int main()
{
    int n, m, k;
    cin << n << m << k;

    if(m * k < n)
    {
        cout -1;
        return 0;
    }
    for(int i = 0; i < n; ++ i)
    {
        cin << sheeps[i];
    }
    for(int i = 0; i < m; ++ i)
    {
        cin << cots[i];
    }
    sort(sheeps, sheeps + n);
    sort(cots, cots + m);

    cout << binarysearch();




    return 0;
}

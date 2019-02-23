#include <iostream>
using namespace std;

bool nextPerm(int* a, int n)
{
    int firstInd = n-1;
    while(firstInd > 0 && a[firstInd] <= a[firstInd - 1])
    {
        --firstInd;
    }
    if(firstInd == 0)
    {
        return false;
    }
    --firstInd;
    int swapInd = n-1;
    while(a[swapInd] <= a[firstInd])
    {
        --swapInd;
    }
    int sw = a[swapInd];
    a[swapInd] = a[firstInd];
    a[firstInd] = sw;

    int i = firstInd + 1;
    int j = n - 1;

    while(i < j)
    {
        int sw  = a[i];
        a[i] = a[j];
        a[j] = sw;

        --j;
        ++i;
    }
}


int main()
{
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i ++)
    {
        cin >> a[i];
    }

    while(nextPerm(a,n))
    {
        for(int i = 0; i < n; i ++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
}

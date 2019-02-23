#include <iostream>
using namespace std;
/*
    ne raboti!
*/
int main()
{
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i ++)
    {
        cin >> a[i];
        --a[i];
    }
    bool used[n];
    int cyclesCount = 0;
    for(int i = 0; i < n; i ++)
    {
        if(used[i])
        {
            continue;
        }
        cout << "Cycle: " << endl << i << " ";
        ++cyclesCount;
        used[i] = true;
        for(int currInd = a[i]; !used[currInd]; currInd = a[currInd])
        {
            cout<< currInd << " ";
            used[currInd] = true;
        }
        cout << endl;
    }
    cout << n - cyclesCount;
}

#include <iostream>
#include <algorithm>
using namespace std;
const int MAX_N = 1000000;
int input[MAX_N][2];
int startings[MAX_N];
int endings[MAX_N];
int n;
/*
    ne raboti!
*/
int binarysearch(int number, int* array)
{
    if(*(array) >= number)
    {
        return 0;
    }

    int l = 0, r = n;
    while(l < r - 1)
    {
        int m = (l + r) / 2;
        if(*(array + m) >= number)
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
    std::ios_base::sync_with_stdio(false);
    cin.tie();

    cin >> n;
    for(int i =0; i < n; i ++)
    {
            cin >> startings[i] >> endings[i];
            input[i][0] = startings[i];
            input[i][1] = endings[i];
    }
    sort(startings,startings + n);
    sort(endings, endings + n);

    for(int i = 0; i < n; i ++)
    {
        cout << n - (binarysearch(input[i][0], startings) + (n - binarysearch(input[i][1], endings))) - 1 << " ";
    }
    cout << endl;
}

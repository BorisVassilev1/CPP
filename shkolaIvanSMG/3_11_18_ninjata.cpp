#include <iostream>
using namespace std;

#define MAX_N 5
int a[MAX_N][MAX_N];
int result[MAX_N][MAX_N];

int min(int a, int b)
{
    if(a != -1 && b != -1)
        return a < b ? a : b;
    else if(a == -1)
        return b;
    else if(b == -1)
        return a;
}

int main()
{
    int n;
    cin >> n;

    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; i ++)
        {
            if(i == 0 && j == 0)
            {
                result[0][0] = 1;
            }
            else
            {
                int optionTop = -1;
                int optionLeft = -1;

                if(i > 0)
                {
                    optionTop = result[i - 1][j] == result[i][j] ? result[i - 1][j] + 2 : result[i - 1][j] + 1;
                }
                if(j > 0)
                {
                    optionLeft = result[i][j - 1] == result[i][j] ? result[i][j - 1] + 2 : result[i][j - 1] + 1;
                }
                result[i][j] = min(optionTop, optionLeft);
            }
        }
    }
    cout << result[n-1][n-1];
    return 0;
}

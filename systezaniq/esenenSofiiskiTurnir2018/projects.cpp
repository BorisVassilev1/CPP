#include <iostream>
using namespace std;
const int MAX_N =  1000000;
int n;
long long projects[MAX_N][3];
int main()
{
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        cin >> projects[i][0] >> projects[i][1];
        for(int j = 0; j < i; ++j)
        {
            if( projects[j][0] <= projects[i][1] && projects[j][1] >= projects[i][0])
            {
                ++projects[i][2];
                ++projects[j][2];
            }
        }
    }
    for(int i = 0; i < n; ++i)
    {
        cout << projects[i][2] <<" ";
    }
}

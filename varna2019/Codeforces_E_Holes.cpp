#include <iostream>
#include <math.h>
using namespace std;

int holes[100000][3];
//[0] -> Ai
//[1] -> kude izliza
//[2] -> sled kolko skoka izliza

int main()/// merzi me da go doarshvam
{
    int n,m;
    cin >> n >> m;
    int sqrtN = sqrt(n);
    for(int i = 0; i < n; i ++) {
        cin >> holes[i][0];
    }
    for(int subArrayInd = 0; subArrayInd < sqrtN; subArrayInd ++)
    {
        for(int i = sqrtN; i >= 0; i --) {
            if(i + holes[i][0] > sqrtN) {
                holes[i + subArrayInd][1] = i + subArrayInd;
                holes[i + subArrayInd][2] = 0;
            }
            else {
                holes[i + subArrayInd][1] = holes[i + holes[i + subArrayInd][0]][1];
                holes[i + subArrayInd][2] = holes[i + holes[i + subArrayInd][0]][2] + 1;
            }
        }
    }
    //for(int i = 0; i < m; i ++) {
        //int command;
    //}
    for(int i = 0; i < n; i ++)
    {
        cout << holes[i][1] << " ";
    }
    cout << '\n';
    for(int i = 0; i < n; i ++)
    {
        cout << holes[i][2] << " ";
    }

}

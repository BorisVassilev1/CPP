#include <iostream>
#include <set>
#include <iterator>
using namespace std;

bool pages[100001];

int main() {
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        pages[a] = true;
        //cout << pages[a];
    }
    int lastK = -1;
    int sheetsCount = 0;
    for(int i = 0; i < 100000; i ++)
    {
        if(pages[i] == 1)
        {
            int K = i % 2 == 0 ? (i - 2) / 2 : (i - 1) / 2;
            //cout << K << " " << lastK << endl;
            if(lastK != K)
            {
                sheetsCount ++;
                lastK = K;

            }
        }
    }
    cout << sheetsCount;
}

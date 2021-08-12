#include <iostream>
#include <math.h>
using namespace std;

long long n;
long long k;
const int MAX_N = 100001;
long long len[MAX_N];
/*
    ne raboti
*/
int numDigits(int x)
{
    int res = 1;
    while(x > 10){
        x /= 10;
        ++res;
    }
}

int digitAtK(int n, int k)
{
    return (n / (int)pow((double)10, (double)(numDigits(n) - k)))%10;
}


int main()
{
    cin >> n >> k;

    len[1] = 1;
    for(int i = 0 ; i <= n; ++i )
    {
        if(len[i-1] > k)
        {
            len[i] = k + 1;
        }
        else
        {
            len[i] = 2 * len[i - 1] + numDigits(i);
        }
        //cout << i << ": " << len[i] << endl;
    }
    if(len[n] <= k)
    {
        cout << -1 << endl;
        return 0;
    }
    while(true)
    {
        if(k <= numDigits(n))
        {
            cout << k <<"-tata cifra na " << n <<  endl << digitAtK(n,k);
            return 0;
        }
        k -= numDigits(n);
        if(k > len[n-1])
        {
            k -= len[n-1];
        }
        n--;
    }

}

#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

int removedDigits = 0;

int main()
{
/*
NE RABOTI!!
*/
    string digits;
    cin >> digits;
    cin >> removedDigits;

    for(int i = 0; i < digits.length() &&  removedDigits > 0; i ++)
    {
        if(digits[i] < digits[i+1])
        {
            //digits[i] = -1;
            if(i >= 1 && digits[i-1]!= -1)
            {
                digits[i] = digits[i-1];
                digits[i-1] = -1;
            }
        }
        else
        {

        }
    }
    for(int i = 0; i < digits.length(); i ++)
    {
        if(digits[i] != -1)
        {
            cout << digits[i];
        }
    }
    return 0;
}

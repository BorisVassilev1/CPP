#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

pair<int, string> results[100];
vector<int> options;

int parseInt(string* a)
{
    string b = *a;
    int result = 0;
    for( int i = 0; i < b.size(); i ++)
    {
        result += pow(10, b.size() - i - 1) * (b.at(i) - '0');
    }
    return result;
}

int main()
{
    //toString(123);
    int n;
    cin >> n;

    for(int i = 0; i < n; i ++)
    {
        cin >> results[i].first >> results[i].second;
    }
    int numlength = results[0].second.size();
    for(int i = 0; i < numlength; i ++)// choosing a "random" digit to assume its correct
    {
        //cout << "digit #" << i << "is correct!\n";
        int digits[3];
        int lastNum;
        for(digits[0] = 0; digits[0] < 10; digits[0] ++)
        {
            for(digits[1] = 0; digits[1] < 10; digits[1]++)
            {
                for(digits[2] = 0; digits[2] < 10; digits[2]++)
                {
                    if(i != 0 && digits[0] == 0)
                        continue;
                    int counter = 0;
                    string currNum;
                    for(int j = 0; j < numlength; j ++)
                    {
                        if(j == i)
                        {
                            currNum.push_back(results[0].second.at(j));
                        }
                        else{
                            currNum.push_back(digits[counter] + '0');
                            counter ++;
                        }
                    }
                    //cout << digits[0] << digits[1] << digits[2] << " ";
                    //cout << currNum << " ";
                    int num = parseInt(&currNum);//the potential correct 1st number
                    if(num == lastNum) continue;
                    lastNum = num;
                    //cout << num << endl;
                    int sum = num + results[0].first;// the sum of the first row
                    //cout << "num: " << num << " sum: " << sum << endl;
                    if(sum % 7 == 0)
                    {
                        //cout << "yuwuidghsaugdf78cuhajukwgteilc ";
                        bool isPossible = true;
                        for(int k = 1; k < n && isPossible; ++ k)// for every row
                        {
                            int Knum = sum - results[k].first;

                            int b = Knum;
                            int digitsCount;
                            for(digitsCount = 1; b > 10; digitsCount ++)
                            {
                                b /= 10;
                            }
                            //cout << digitsCount << endl;
                            string KnumStr;
                            for(int i = digitsCount - 1; i >= 0; -- i)
                            {
                                int power = (int)pow(10, i);
                                power % 10 == 9 ? power += 1 : 0;
                                //cout << a << " % "<< power << " = " << a % power << endl;
                                KnumStr.push_back(Knum / power + '0');
                                Knum %= (power);

                            }

                            //string KnumStr = to_string(Knum);
                            if(KnumStr.length() != results[k].second.length())
                            {
                                isPossible = false;
                                break;
                            }
                            int sameDigitsCount = 0;
                            for(int j = 0; j < KnumStr.length() ; j ++)
                            {
                                if(KnumStr.at(j) == results[k].second.at(j))
                                {
                                    ++ sameDigitsCount;
                                }
                            }
                            if(sameDigitsCount != 1)
                            {
                                isPossible = false;
                            }
                            //cout << "currNum: " << currNum << " Sum: " << sum << " Row: " << k << " KNumStr: " << KnumStr << " [row].second: " << results[k].second << " SameDigits: " << sameDigitsCount << " isPossible: " << isPossible << endl;

                        }
                        if(isPossible)
                        {
                            options.push_back(sum/7);
                        }
                    }
                    //cout<< endl;
                }
            }
        }
    }
    cout << options.size() << endl;
    for(vector<int>::iterator i = options.begin(); i != options.end(); ++ i)
    {
        cout << *i << " ";
    }
}

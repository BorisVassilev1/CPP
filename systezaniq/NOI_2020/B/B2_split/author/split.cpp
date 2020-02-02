#include<iostream>
using namespace std;

string s;

int main()
{
  cin >> s;

  int c=0, c0=0, c1=0;
  for(int i=0;i<s.size();i++)
  {
    if(s[i]=='0') c0++; else c1++;
    if(c0==c1){c++;c0==0;c1==0;}
  }

  cout << c << endl;
}

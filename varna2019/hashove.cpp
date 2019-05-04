#include <iostream>
#include <string>
#define D(a) std::cout << #a << ": " << a <<std::endl;
typedef unsigned long long ll;

const ll MOD = 1e9+7;
const ll BASE = 29;

int main()
{
    ///n - hay.size();
    ///m - needle.size();

    std::string hay, needle;
    //std::cin >> hay >> needle;
    std::getline(std::cin,hay);
    std::getline(std::cin, needle);

    ll pow[1000];
    pow[0] = 1;
    //O(m)
    for(int i = 1; i < needle.size(); i ++)
            pow[i] = (pow[i-1] * BASE) % MOD;

    ll needleHash = 0;
    ll currHayHash = 0;
    //O(m)
    for(int i = 0; i < needle.size(); i ++) {
        needleHash *= BASE;
        needleHash += needle[i];
        //needleHash %= MOD;

        currHayHash *= BASE;
        currHayHash += hay[i];
        //currHayHash %= MOD;
    }

    if(currHayHash == needleHash)
    {
        std::cout << "Match at 0\n";
    }

    for(int i = 0; i < hay.size(); i++)
    {
        //remove hay[i]
        //add hay[i + needle.size()]
        currHayHash -= hay[i] * pow[needle.size() - 1];
        currHayHash *= BASE;
        currHayHash += hay[i + needle.size()];
        //D(currHayHash);
        //std::cout << hay.substr(i + 1; needle.size()) << std::endl;
        if(currHayHash == needleHash) {
                //std::cout << std::string(i + 1, ' ') << '^';
                std::cout << "Match at " << i + 1 << std::endl;
        }
    }

}

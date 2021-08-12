#include <iostream>
#include <string>

int main() {
    std::string in;
    std::string out1;
    std::string out2;
    int T;
    std::cin >> T;
    for(int t = 0; t < T; t ++)
    {
        bool shouldPutZeroes = false;
        std::cin >> in;
        for(int i = 0; i < in.size(); i ++) {
            if(in[i] == '4')
            {
                out1 += '3';
                out2 += '1';
                shouldPutZeroes = true;
            }
            else {
                out1 += in[i];
                if(shouldPutZeroes) {
                    out2 +='0';
                }
            }
        }
        std::cout << "Case #" << t  << ": "<< out1 << " " << out2 << '\n';
        out1 = "";
        out2 = "";
    }
}

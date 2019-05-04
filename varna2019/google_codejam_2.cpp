#include <iostream>
#include <string>
int main() {
    int T;
    std::cin >> T;
    for(int t = 0; t < T; t ++) {
        int N;
        std::cin >> N;
        std::string in;
        std::string out;
        std::cin >> in;
        for(int i = 0; i < in.size(); i ++)
        {
            if(in[i] == 'E') out += 'S';
            else out += 'E';
        }

        std::cout << "Case " << t + 1 << ": " << out << '\n';
        out = "";
    }
}

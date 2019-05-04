#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
/*
 * WORKS WITH ELEMENTARY OPERATIONS AND IS SUPER FAST!!
 * THE "MANDELBROTH SET" CODE HAS NOT-MATCHING BRACKETS!!!
*/
int main() {
    string brainFuckCode;
    cin >> brainFuckCode;
    ofstream outFile;
    outFile.open("outputFile.cpp");
    outFile << "#include <iostream>\n";
    outFile << "using namespace std;\n";
    outFile << "char array[65536] = {0};\n";
    outFile << "char* ptr = array;\n";
    outFile << "int main() {\n";

    int counter1 = 0;
    int counter2 = 0;
    for(int i = 0; i < brainFuckCode.length(); i ++)
    {
        switch(brainFuckCode[i])
        {
            case '>': {
                outFile << "++ptr;\n";
            }
                break;
            case '<': {
                outFile << "--ptr;\n";
            }
                break;
            case '+': {
                outFile << "++*ptr;\n";
            }
                break;
            case '-': {
                outFile << "--*ptr;\n";
            }
                break;
            case '.': {
                outFile << "cout << *ptr;\n";
            }
                break;
            case ',': {
                outFile << "cin >> *ptr;\n";
            }
                break;
            case '[': {
                outFile << "while(*ptr != 0) {\n";
                counter1 ++;
            }
                break;
            case ']': {
                outFile << "}\n";
                counter2 ++;
            }
        }
    }
    outFile << "}\n";
    if(counter1 != counter2)
    {
        cout << "your code is invalid" << endl;
    }
    else
    {
            cout << "your code is valid" << endl;
        /*for(int i = 0; i < counter1 - counter2; i ++)
        {
            outFile << "}\n";
        }*/
        outFile.close();
        std::system("g++ -o program outputFile.cpp"); // compile
        std::system("program.exe"); // run
        return 0;
    }
}

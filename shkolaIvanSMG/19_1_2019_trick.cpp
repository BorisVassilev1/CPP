#include <iostream>
using namespace std;
const int MAX_SIZE = 100000;
char operations[MAX_SIZE];
int numbers[MAX_SIZE];

int main(){
    //ios_base::sync_with_studio(false);
    //cin.tie(0);

    int counter = 0;
    while(true)
    {
        char c;
        cin >> c;
        if(c == '=')
        {
            break;
        }
        else{
            operations[counter] = c;
            cin >> numbers[counter];
            counter ++;
        }
    }
    int result;
    cin>> result;


    for(int i = counter - 1; i >= 0; --i)
    {
        switch(operations[i])
        {
            case '*' :
            {
                result /= numbers[i];
                break;
            }
            case '/' :
            {
                result *= numbers[i];
                break;
            }
            case '+' :
            {
                result -= numbers[i];
                break;
            }
            case '-' :
            {
                result += numbers[i];
            }
        }

    }
    cout << result;

}

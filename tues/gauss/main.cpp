#include <iostream>
#include <iomanip>
using namespace std;

float** a;

void print(float** a, int m, int n) {
    cout << endl;
    for(int i = 0; i < m; i ++) {
        for(int j = 0; j < n; j ++) {
            cout << " " << a[i][j];
        }
        cout << endl;
    }
}

void gauss(float** mat, int m, int n) {
    for(int curr_row = 0, curr_col = 0; curr_col < n-1; curr_col ++) {
        /*int max_row = -1;
        float max_val = -1;
        for(int i = curr_row; i < m; i ++) {
            float _abs = abs(mat[i][curr_col]);
            if(_abs > max_val) {
                max_val = _abs;
                max_row = i;
            }
        } 
        
        if(max_row != curr_row) {
            for(int i = curr_row; i < n; i ++) {
                swap(mat[max_row][i], mat[curr_row][i]);
            }
        }*/

        if(mat[curr_row][curr_col] == 0) {
            cout << "skip" << endl;
            continue;
        }
        for(int i = curr_row + 1; i < m; i ++) {
            float coef = mat[i][curr_col] / mat[curr_row][curr_col];
            for(int k = 0; k < n; k++) {
                mat[i][k] -= mat[curr_row][k] * coef;
            }
        }

        curr_row ++;
       cout << "asda"; 
        print(a, m, n);

        cout << "Asd:";
    }
    cout << "asda";
    for(int curr_row = m-1, curr_col = n-1; curr_col >= 0;) {
        cout << curr_row << " " << curr_col;
        if(mat[curr_row][curr_col] == 0) {
            if(mat[curr_row][n-1] != 0) {
                cout << "no solution!";
                return;
            }
            else {
                curr_row --;
                continue;
            }
        }
        //int val = mat[curr_row][n-1] / mat[curr_row][curr_col];
        //cout << "x" << curr_col << " = " << val;
        curr_col --;
       
    } 
    
}


int main() {
    int m, n;
    cin >> m >> n;
    
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    cout << showpos;
    a = new float*[m];
    for(int i = 0; i < m; i ++) {
        a[i] = new float[n + 1];
    }

    for(int i = 0; i < m; i ++) {
        for(int j = 0; j < n + 1; j ++) {
            cin >> a[i][j];
        }
    }
    
    gauss(a, m, n+1);
    
    print(a, m, n+1);
    
    for(int i = 0; i < m; i ++) {
        delete [] a[i];
    }
}

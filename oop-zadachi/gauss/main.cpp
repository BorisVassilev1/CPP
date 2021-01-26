#include <iostream>
#include <iomanip>
#include <vector>
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
        int max_row = -1;
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
        }

        if(mat[curr_row][curr_col] == 0) {
            continue;
        }
        for(int i = curr_row + 1; i < m; i ++) {
            float coef = mat[i][curr_col] / mat[curr_row][curr_col];
            for(int k = 0; k < n; k++) {
                mat[i][k] -= mat[curr_row][k] * coef;
            }
        }

        curr_row ++;
        print(a, m, n);
    }
    
    vector<int> variables;
    for(int curr_row = m-1, curr_col = n-2; curr_col >= 0 && curr_row >= 0;) {
        //cout << endl << curr_row << " " << curr_col << endl;
        if(mat[curr_row][curr_col] == 0) {
            if(mat[curr_row][n-1] != 0) {
                cout << "no solution!" << endl;
                return;
            }
            else {
                curr_row --;
                continue;
            }
        } else {
            if(curr_col > 0 && mat[curr_row][curr_col - 1] != 0) {
                cout << "x" << curr_col + 1 << " is variable." << endl;
                variables.push_back(curr_col);
                curr_col --;
                continue;
            } 
        }

        float val = mat[curr_row][n-1];
        float coef = mat[curr_row][curr_col];
        cout << "x" << curr_col + 1 << " = (" << val;

        bool is_variable = false;
        for(int i = 0; i < (int)variables.size(); i ++) {
            int id = variables[i];
            if(id == curr_col) break;
            float coef = mat[curr_row][id];
            if(coef != 0) {
                is_variable = true;
                variables.push_back(curr_col);
                cout << " - (" << coef << ")*x" << id + 1 << flush;
            }
        }
        cout << ") / " << coef << flush; 
        cout << endl;
        
        if(is_variable) {
            curr_col --;
            continue;
        }

        for(int i = curr_row-1; i >= 0; i -- ) {
            mat[i][n-1] -= val * mat[i][curr_col];
            mat[i][curr_col] = 0;
        }
        
        curr_col --;
        curr_row --;
       
    } 
    
}


int main() {
    int m, n;
    cin >> m >> n;
    
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    //cout << showpos;
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

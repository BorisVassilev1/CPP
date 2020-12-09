#include <iostream>

using namespace std;

float** a;


void gauss(float** mat, int m, int n) {
    for(int i = 0; i < m; i ++) {
        cout << "lol" << endl;
        //find max
        int max_row = -1;
        float max_val = 0;
        for(int j = i; j < m; j++) {
            int _abs = abs(mat[j][i]);
            if(_abs > max_val) {
                max_val = _abs;
                max_row = j;
            }
        }
        
        cout << "kek"<< endl;

        //move that line up
        if(max_row != i) {
            for(int j = 0; j < n; j ++ ) {
                swap(mat[max_row][j], mat[i][j]);
            }
        }
        cout << "kekw" << endl;
        //make all 0
        for(int j = i + 1; j < m; j ++) {
            float coef = mat[j][i] / mat[i][i];
            for(int k = 0; k < n; k ++) {
                mat[j][k] -= mat[i][k] * coef; 
            }
        }

        cout << "asdad" << endl;
    }
}


int main() {
    int m, n;
    cin >> m >> n;

    a = new float*[m];
    for(int i = 0; i < m; i ++) {
        a[i] = new float[n + 1];
    }
    
    cout << "asdf";
    for(int i = 0; i < m; i ++) {
        for(int j = 0; j < n + 1; j ++) {
            cin >> a[i][j];
        }
    }
    cout << "wtf" << flush;
    gauss(a, m, n+1);

    cout << endl;
    for(int i = 0; i < m; i ++) {
        for(int j = 0; j < n + 1; j ++) {
            cout << " " << a[i][j];
        }
        cout << endl;
    }

}

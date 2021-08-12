#include <iostream>
using namespace std;

class Matrix{
public:
    int matrix[5][5];
    Matrix matMul(Matrix A, Matrix B, int size)
    {
        Matrix res;
        for(int x = 0; x < size; x ++)
        {
            for( int y = 0; y < size; y ++)
            {
                for(int k = 0; k < size; k ++)
                {
                    res.matrix[x][y] += A.matrix[x][k] * B.matrix[k][y];
                }
            }
        }
        return res;
    };

    Matrix matPow(Matrix A, int size, int power)
    {
        if(power == 2)
        {
            return matMul(A, A, size);
        }
        else if(power % 2 == 1)
        {
            return matMul(matPow(A, size, power - 1), A, size);
        }
        else if(power % 2 == 0)
        {
            Matrix b = matPow(A, size, power / 2);
            return matMul(b,b, size);
        }
    };
};



int main()
{
    int n, k;
    cin >> n >> k;

    Matrix sol;
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            cin >> sol.matrix[i][j];
        }
    }
    sol = sol.matPow(sol, n, k);

    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j ++)
        {
            cout << sol.matrix[i][j];
        }
        cout << endl;
    }
}




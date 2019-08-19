#include <iostream>
using namespace std;

int arr[12] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
int tree[12];
int n = 12;

void updateBiTree(int* biTree, int n, int i, int val) {
    ++ i;
    while( i < n +1) {
        //cout << i << " -> ";
        biTree[i - 1] += val;
        //cout << biTree[i-1] << " ";
        i += i & (-i);
    }
    //cout << " -> " << val << " ";
    //cout<< endl;
}

void constructBiTree(int* biTree,int* arr, int n) {

    for( int i = 0; i < n; i ++) {
        biTree[i] = 0;
        //cout << biTree[i] << " ";
    }
    //cout << endl << endl;
    for(int i = 0; i < n; i ++) {
        updateBiTree(biTree, n, i, arr[i]);
    }
    for(int i = 0; i < n; i ++) {
        cout << biTree[i] << " ";
    }
    cout << endl;

    //return biTree;
}



int main() {
    constructBiTree(tree, arr, n);
    for(int i = 0; i < n; i ++) {
        cout << tree[i] << " ";
    }
}

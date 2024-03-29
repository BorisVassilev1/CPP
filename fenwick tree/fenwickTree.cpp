#include <iostream>
using namespace std;

int arr[12] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
int tree[12];
int n = 12;

void updateBiTree(int* biTree, int n, int i, int val) {
    ++ i;
    while( i < n +1) {
        biTree[i - 1] += val;
        i += i & (-i);
    }
}

void constructBiTree(int* biTree,int* arr, int n) {

    for( int i = 0; i < n; i ++) {
        biTree[i] = 0;
    }
    for(int i = 0; i < n; i ++) {
        updateBiTree(biTree, n, i, arr[i]);
    }

}

int sumBiTree(int* biTree, int i) {
    i += 1;
    int sum = 0;
    while( i > 0) {
        sum += biTree[i];
        i -= i&(-i);///????
    }
    return sum;
}


int main() {
    for(int i = 0; i < n; i ++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    constructBiTree(tree, arr, n);
    for(int i = 0; i < n; i ++) {
        cout << tree[i] << " ";
    }
    cout << endl;
    cout << sumBiTree(tree,3);
}


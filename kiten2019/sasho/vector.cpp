#include <iostream>
using namespace std;

int log(int a) {
    int i = 0;
    for(;a >= (1 << (i + 1)); i ++) {
    }
    return i;
}

struct MiniVector {
    int *arr;
    MiniVector *next;
    int length;
    MiniVector(int length) : length(length){
        arr = new int[length];
        next = nullptr;
    }
    int &operator [] (int i) const{
        return arr[i];
    }
    ~MiniVector() {
        delete[] arr;
        delete next;
    }
};

struct Vector {
    MiniVector *first, *last;
    int lastPowerOf2 = 0;
    int current_length = 0;
    Vector() {
        first = nullptr;
        last = nullptr;
    }
    void pushBack(int val) {
        if(current_length < (1 << lastPowerOf2) - 1) {
            (*this)[current_length] = val;
            current_length ++;
            return;
        }


        if(current_length == 0) {
                //cout << "extending the array 1";
            MiniVector *newArr = new MiniVector(2);
            //lastPowerOf2 ++;
            cout << lastPowerOf2 << endl;
            first = newArr;
            last = newArr;
        }
        if(current_length == 1 << (lastPowerOf2 + 1)) {
            //cout << "extending the array";
            lastPowerOf2 ++;
            MiniVector *newArr = new MiniVector(1 << lastPowerOf2);
            cout << "adding " << (1 << lastPowerOf2) << " " << current_length << endl;
            //lastPowerOf2 ++;
             cout << lastPowerOf2 << endl;
            last -> next = newArr;
            last = newArr;
        }
        (*this)[current_length] = val;
        current_length ++;
        return;

    }

    void popBack() {
        (*this)[current_length - 1] = 0;
        current_length --;
        //cout << (1 << lastPowerOf2);
        if(current_length == 1 << lastPowerOf2) {
            //delete last;
            cout << "deleting. " << "length is " << current_length;
            MiniVector *current = first;
            while(current -> next != last) {current = current -> next;}
            current -> next = nullptr;
            delete last;
            last = current;
            lastPowerOf2 --;
        }
    }

    int &operator [] (int i) const{
        int arraysToPass = log(i);

        MiniVector *current = first;
        for(int i = 0; i < arraysToPass; i ++) {
            current = current -> next;
            if(current == nullptr) {
                throw new exception();
            }
        }
        return (*current)[i - (1 << arraysToPass)];
    }

    ~Vector() {
        delete first;
        first = nullptr;
        last = nullptr;
    }
};

int main() {
    Vector a = *(new Vector());
    a.pushBack(1);
    a.pushBack(2);
    a.pushBack(3);
    a.pushBack(4);
    a.pushBack(5);
    cout << a[0] << a[1] << a[2] << a[3] << a [4] << endl;
    a.popBack();
    a.popBack();
    a.popBack();
    cout << endl;
    cout << a[0] << a[1] ;
    cout << endl;
    delete &a;
}

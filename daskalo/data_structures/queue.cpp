#include <iostream>

using namespace std;

template<class T>
class queue {

    T* data;
	
	int begin = 0;
	int end = 0;
	
	int length = 0;
	int limit;
	
	static int initial_length;
	
	void resize() {
		data = (T*)realloc(data, limit * 2 * sizeof(T));
        for(int i = begin; i < limit; i ++) {
            data[i + limit] = data[i];
        }
        begin += limit;
        limit *= 2;
    }

    public:

    queue() : limit(initial_length) {
        data = (T*)malloc(initial_length * sizeof(T));
    }

    int size() {
        return length;
    }

    bool empty() {
        return length == 0;
    }

    T& front() {
        return data[begin];
    }

    T& back() {
        return data[end - 1];
    }

    void push(const T& val) {
        if(length == limit) resize();
        data[end] = val;
        ++end;
        end %= limit;
        ++length;
    }

    void pop() {
        if(empty()) return;
        ++begin;
        begin %= limit;
        --length;
    }

    void print_all() {
        for(int i = 0; i < limit; ++ i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};
template<class T>
int queue<T>::initial_length = 5;

int main() {
    queue<int> q;

    cout << q.empty() << endl;

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    cout << q.size() << endl << endl;
    q.print_all();
    q.push(5);
    q.push(6);
    //q.push(7);
    //q.push(8);
    q.print_all();    

    while(!q.empty()) {
        cout << q.front() << " " << flush;
        q.pop();
    }
    cout << endl;
}

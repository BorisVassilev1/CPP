<<<<<<< Updated upstream
#include <iostream>

=======
>>>>>>> Stashed changes
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
};
template<class T>
int queue<T>::initial_length = 5;
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes

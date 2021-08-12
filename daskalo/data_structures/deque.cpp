#include <iostream>

using namespace std;

template<class T>
class deque {

    static const int buff_size = 10;

    T **data;

    int buffers_count = 1;

    //int begin_offset = 0; // offset from the beginning of the first array for the begin() iterator
    //int end_offset = 0; // offset from the beginning of the last array for the end() iterator
    
    int length = 0;

    void alloc_back() {
        data = (T**)realloc(data, ++buffers_count);
        data[buffers_count - 1] = new T[buff_size];
    }

    void alloc_front() {
        data = (T**)realloc(data, ++buffers_count);
        for(int i = buffers_count - 2; i >= 0; i --) {
            data[i + 1] = data[i];
        }
        data[0] = new T[buff_size];
    }

    public: 

    deque() : begin_it(this, 0, 0), end_it(this, 0, 0){
        data = (T**)calloc(1, sizeof(T*));
        data[0] = new T[buff_size];
    }
    
    ~deque() {
        //TODO: delete data
    }

    class iterator {
        friend class deque;

        const deque *d;
        int array_index, subarray_index;

        iterator(const deque* d, const int& array_index, const int& subarray_index) : d(d), array_index(array_index), subarray_index(subarray_index) {}

        public:

        iterator& operator ++ (const int _) {
            array_index += (++ subarray_index) / buff_size;
            subarray_index %= buff_size;
            return *this;
        }

        iterator& operator -- (const int _) {
            array_index -= (--subarray_index) < 0;
            subarray_index %= buff_size;
            return *this;
        }

        iterator& operator += (const int i) {
            if(i < 0) return *this -= -i;
            subarray_index += i;
            array_index += subarray_index / buff_size;
            subarray_index %= buff_size;
            return *this; 
        }

        iterator& operator -= (const int i) {
            if(i < 0) return *this += -i;
            
            subarray_index -= i;
            array_index -= (subarray_index / buff_size) + subarray_index < 0;
            return *this;
        }

        T& operator * () {
            return d->data[array_index][subarray_index];
        }

        bool operator == (const iterator &other) const {
            return d == other.d && array_index == other.array_index && subarray_index == other.subarray_index;
        }

        bool operator != (const iterator &other) const {
            return !(*this == other);
        }
        
    };

    iterator& begin() {
        return begin_it;
    }

    iterator& end() {
        return end_it;
    }

    void push_back(const T &value) {
        if(end_it.subarray_index == 0 && length != 0) {
            alloc_back();
        }   
        *end_it = value;
        end_it ++;
        
        length ++;
    }

    void push_front(const T &value) {
        if(begin_it.subarray_index == 0) {
            alloc_front();
            begin_it += buff_size - 1;
            end_it += buff_size;

        } else {
            begin_it--;
        }
        *begin_it = value;
        length ++;
    }

    T& operator [] (const int &i)const {
        if(i >= length) throw out_of_range("no such element");
        int real_i = i + begin_it.subarray_index;
        return data[real_i / buff_size][real_i % buff_size];
    }

    int size() {
        return length;
    }
    
    void pop_front() {
        begin_it ++;   
    }

    void pop_back() {
        end_it --;
    }
    
    

    private:

    iterator begin_it;
    iterator end_it;

 
};


int main() {

    deque<int> d;
    
    d.push_back(1);
    d.push_back(2);
    d.push_back(3); 
    d.push_back(4);
    d.push_back(5);
    d.push_back(6);
    d.push_back(7);
    d.push_back(8);
    d.push_back(9);
    d.push_back(10);
    
    for(auto it = d.begin(); it != d.end(); it ++) {
        cout << *it << " " << endl;
    }
    cout << endl;

    
    for(int i = 0; i < d.size() ; i ++) {
        cout << d[i] << " " << flush;
    }
    cout << endl;


    d.push_back(11);
    d.push_back(12);
    d.push_back(13);
    d.push_back(13);
    d.push_back(14);
    d.push_back(15);
    d.push_back(16);
    
    for(auto i = d.begin(); i != d.end() ; i ++) {
        cout << *i << " " << flush;
    }
    cout << endl;


    d.push_front(-1);
    d.push_front(-2);
    d.push_front(-3);

    for(auto i = d.begin(); i != d.end() ; i ++) {
        cout << *i << " " << flush;
    }
    cout << endl;
    
    d.pop_front();
    d.pop_back();
    d.pop_front();
    d.pop_front();
    d.pop_front();
    d.push_front(10);
    d.push_back(42);

    for(auto i = d.begin(); i != d.end() ; i ++) {
        cout << *i << " " << flush;
    }
    cout << endl;
}

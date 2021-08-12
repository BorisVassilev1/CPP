template<class T>
class stack { // implementaciq na stack chrez dinamichen masiv
    
    T* arr; // masiva, koito she polzvame
    int length; // duljinata
    int limit; // duljinata na masiva
    
    public: 
    
    stack() : stack(1) {}
    
    stack(int length) : length(0), limit(length) {
        arr = (T*)malloc(length * sizeof(T)); // zadelqme pamet
    }

    ~stack() {
        free(arr); // osvobojdavame pametta
    }
    
    bool empty() {
        return length == 0;
    }

    void push(const T& value) {
        T val(value); 
        if(length == limit) { // ako masiva e pulen
            limit *= 2;
            arr = (T*)realloc(arr, limit * sizeof(T)); // zadeli 2 puti poveche pamet
        }
        arr[length++] = val;
    }

    void pop() {
        if(length >= 0)
            length --; // mi prosto namalqvame duljinata
    }

    T& top() {
        return arr[length - 1]; // posledniq element
    }

    int size() {
        return length;
    }
};


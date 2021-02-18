#include <iostream>

using namespace std;

template<class T>
class list {

    struct list_node {
        T value;
        list_node *prev, *next;

        list_node(const T& value, list_node * const & prev, list_node * const & next) : value(value), prev(prev), next(next) {}
    };

    list_node *first = nullptr, *last = nullptr;

    int length = 0;

    public:

    list() {
        list_node *dummy = new list_node(0, nullptr, nullptr);

        first = dummy;
        last = dummy;
    }

    class iterator {
        friend class list;

        list_node *node;

        iterator(list_node * const &node) : node(node) {}

        public:

        iterator& operator ++ (const int _) {
            node = node->next;
            return *this;
        }

        iterator& operator -- (const int _) {
            node = node->prev;
            return *this;
        }

        const T& operator * () const {
            return node->value;
        }

        bool operator == (const iterator &other) const {
            return node == other.node;
        }

        bool operator != (const iterator &other) const {
            return node != other.node;
        }
    };

    bool is_empty() {
        return first == last;
    }

    void push(const iterator& it, const T& value) {
        if(it.node == nullptr) throw out_of_range("iterator out of range or invalid");

        list_node *node = new list_node(value, it.node->prev, it.node);

        if(it.node->prev == nullptr) {
            first = node;
        } else {
            it.node->prev->next = node;
        }
        it.node->prev = node;

        length ++;
    }

    iterator begin() const {
        return iterator(first);
    }

    iterator end() const {
        return iterator(last);
    }

    void push_back(const T& value) {
        push(end(), value); 
    }

    void push_front(const T& value) {
        push(begin(), value);
    }

    void pop(const iterator& it) {
        if(it == end() || it.node == nullptr) throw out_of_range("iterator out of range or invalid");

        auto prev = it.node->prev;
        auto next = it.node->next;

        if(prev == nullptr) {
            first = next;
        } else {
            prev->next = next;
        }
        next->prev = prev;

        delete it.node;
    }

    void pop_front() {
        pop(begin());
    }

    void pop_back() {
        pop(end() -- );
    }
};


int main() {

    list<int> l;

    l.push_back(1);
    l.push_back(2);
    l.push_front(3);
    
    for(list<int>::iterator it = l.begin(); it != l.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    
    auto i = l.begin() ++ ++;
    l.push(i, 4);
    
    for(list<int>::iterator it = l.begin(); it != l.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;

    i --;
    l.pop(i);
    
    for(list<int>::iterator it = l.begin(); it != l.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;

    l.pop_front();
    
    for(list<int>::iterator it = l.begin(); it != l.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    
    l.pop_back();

    for(list<int>::iterator it = l.begin(); it != l.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
}

#include <iostream>

template <class T>
class stack { // implementaciq na stack chrez svurzan spisak
    struct stack_node { // vruh na grafa
        const T value; // dannata
        const stack_node* next; // ukazatel kum sledvashtiq vruh
    
        stack_node(const T& value, const stack_node* next) : value(value), next(next) {}
    };
    
    int length = 0;
    stack_node* first = nullptr; // posledniq element

public:
    bool is_empty() const{
        return first == nullptr; // ako nqma purvi vruh
    }

    void push(const T& value) {
        first = new stack_node(value, first); // zadelqme pamet dinamichno za novoto chislo
        length ++;
    }

    void pop() {
        if(is_empty()) return; // ne moje da popvame prazen stack
        stack_node* curr = first; 
        first = (stack_node*) first->next;
        delete curr; // osvobojdavame pamet
        length --;
    }
    
    const T& top() const {
        return first->value;
    }

    int size() {
        return length;
    }
};


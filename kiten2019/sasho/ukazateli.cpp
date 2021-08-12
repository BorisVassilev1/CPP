#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* next;
    Node(int a) {
        data = a;
        next = nullptr;
    }
    void print() {cout << data;}
};

struct DoubleNode {
    int data;
    DoubleNode *previous, *next;
    DoubleNode(int data, DoubleNode *previous, DoubleNode *next) : data(data), previous(previous), next(next) {}
    void print() {cout << data; }
};

struct LinkedList {
    Node *first, *last;
    linkedList() {
        first = nullptr;
        last = nullptr;
    }

    void addNode(int data) {
        Node *newNode = new Node(data);
        if(first == nullptr) {
            first = newNode;
            last = newNode;
        }
        else {
            last->next = newNode;
            last = newNode;
        }
    }

    void addNodeAt(int position,int data) {
        if( position == 0) addNode(data);
        Node *current = first;
        for(int i = 0; i < position; i ++) {
            current = current->next;
        }
        Node *newNode = new Node(data);
        newNode->next = current->next;
        current->next = newNode;
    }

    void print() {
        Node *current = first;
        while(current != last->next) {
            current->print();
            cout << " ";
            current = current->next;
        }
        cout << endl;
    }

    LinkedList *filterOnlyEven() {
        LinkedList *ll = new LinkedList();
        Node *current = first;
        while(current != nullptr) {
            if(current->data % 2 == 0) {
                ll->addNode(current->data);
                //cout << "asasa" << (*current).data;
            }
            current = current->next;
        }
        return ll;
    }
    Node *getNode(int position) {
        Node *current = first;
        for(int i = 0; i < position; i ++) {
            current = current->next;
        }
        return current;
    }

    Node *middleElement() {
        Node *current = first;
        Node *currentDouble = first;
        while(currentDouble != nullptr) {
            currentDouble = currentDouble->next;
            if(currentDouble == nullptr)
                break;
            currentDouble = currentDouble->next;
            current = current->next;
        }
        return current;
    }
};

struct DoubleLinkedList {
    DoubleNode *first, *last;

    DoubleLinkedList() {
        first = nullptr;
        last = nullptr;
    }

    void addNode(int data) {
        DoubleNode *newNode = new DoubleNode(data, last, nullptr);
        if(first == nullptr) {
            newNode->previous = nullptr;
            first = newNode;
            last = newNode;

        }
        else {
            last->next = newNode;
            last = newNode;
        }
    }

    void AddNodeAt(int data, int position) {
        DoubleNode *current = first;
        for(int i = 0; i < position ; i ++) {
            current = current->next;
        }
        DoubleNode *newNode = new DoubleNode(data, current, current->next);
        if(current->next != nullptr)
        current->next->previous = newNode;

        current->next = newNode;
    }

    void print() {
        DoubleNode *current = first;
        while(current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    DoubleLinkedList *filterOnlyEven() {
        DoubleLinkedList *ll = new DoubleLinkedList();
        DoubleNode *current = first;
        while(current != nullptr) {
            if(current->data % 2 == 0)
                ll->addNode(current->data);
            current = current->next;
        }
        return ll;
    }

    DoubleNode *middleElement() {
        DoubleNode *current = first;
        DoubleNode *doubleCurrent = first;
        while(doubleCurrent != nullptr)
        {
            doubleCurrent = doubleCurrent->next;
            if(doubleCurrent == nullptr) break;
            doubleCurrent = doubleCurrent->next;
            current = current->next;
        }
        return current;
    }
};
int main() {
    DoubleLinkedList ll = *(new DoubleLinkedList());

    ll.addNode(1);
    ll.addNode(2);
    ll.addNode(3);
    ll.addNode(5);
    ll.AddNodeAt(4,2);
    ll.addNode(6);
    ll.print();

    DoubleLinkedList ll2 = *(ll.filterOnlyEven());
    ll2.print();
    ll.print();

    ll.middleElement()->print();
}

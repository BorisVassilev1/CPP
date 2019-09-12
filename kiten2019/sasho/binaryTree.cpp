#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *child1, *child2;
    Node(int data) : data(data) {child1 = nullptr; child2 = nullptr;}
    void print() {
        cout << data;
    }
};

struct BinaryTree {
    Node *root;

    BinaryTree() {
        root = nullptr;
    }

    bool addNode(int data) {
        Node *newNode = new Node(data);
        if(root == nullptr) {
            root = newNode;
            return true;
        }
        Node *current = root;
        while(current != nullptr) {
            if(data < current -> data) {
                    if(current -> child1 == nullptr) {
                        current -> child1 = newNode;
                        return true;
                    }
                    current = current -> child1;
            }
            else if(data > current -> data) {
                    if(current -> child2 == nullptr) {
                        current -> child2 = newNode;
                        return true;
                    }
                    current = current -> child2;
            }
            else return false;
        }

    }
    void print() {
        printRec(root);
    }
    void printRec(Node *a) {
        if(a -> child1 != nullptr) {
            printRec(a->child1);
        }
        a->print();
        cout << " ";
        if(a -> child2 != nullptr) {
            printRec(a->child2);
            cout << " ";
        }

    }

};



int main() {
    BinaryTree bt = *(new BinaryTree());
    bt.addNode(5);
    bt.addNode(4);
    bt.addNode(3);
    bt.addNode(2);
    bt.addNode(1);
    bt.addNode(6);
    bt.print();
}

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;
int m;


struct Node {
    vector<int> neighbours;
    bool seen;
    int currentGroupSize;
    Node() {
        seen = false;
        currentGroupSize = 1;
        //neighbours = *(new vector<int>());
    }


    ~Node() {
        delete &neighbours;
    }
};

Node *tree;
queue<Node> q;
int usedEdges = 0;
int main() {
    //q = *(new queue<Node>());
    cin >> n >> m;
    //cout << "asas";
    tree = new Node[n];
    //cout << "treew";
    for(int i = 0; i < m; i ++) {
        int from, to;
        cin >> from >> to;
        //cout << from << to;
        tree[from - 1].neighbours.push_back(to - 1);
        tree[to - 1].neighbours.push_back(from - 1);
    }
    //cout << "sddfs";
    for(int i = 0; i < n; i ++) {
        if(tree[i].neighbours.size() == 1) {
            q.push(tree[i]);
            tree[i].seen = true;
        }
    }
    //cout << "asda";
    while(!q.empty()) {
        Node curr = q.front();
        for(int i = 0; i < curr.neighbours.size(); i ++) {
                //cout << "asas";
            if(tree[curr.neighbours[i]].seen == false) {
                q.push(tree[curr.neighbours[i]]);
                usedEdges ++;
                cout << usedEdges;
                cout << " " << curr.neighbours[i];
                tree[curr.neighbours[i]].seen = true;
            }
            //if(usedEdges > m)
            //    break;
        }
        q.pop();
    }

}

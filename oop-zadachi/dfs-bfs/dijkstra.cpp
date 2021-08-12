#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <queue>
using namespace std;

vector<vector<int>> G;

void print() {
    cout << G.size() << endl;
    for (int i = 0; i < G.size(); ++i) {
        cout << i + 1 << ": ";
        for (int j = 0; j < G[i].size(); ++j) {
            cout << G[i][j] + 1 << " ";
        }
        cout << endl;
    }
}


bool dijkstra(int s, int e) {
	priority_queue<pair<int, int> > q;
	vector<bool> visited(G.size(), false);

	q.push({0, s});

	while(!q.empty()) {
		auto curr = q.top();
		q.pop();
		for(int i = 0; i < G[curr.second].size(); i ++) {
			int next = G[curr.second][i];
			if(!visited[next]) {
				q.push({curr.first + 1 ,next});
				visited[next] = true;
			}
		}
	}
	cout << distance[e];
	return false;
}

int main() {
	fstream file("graph.txt");

	int n;
	file >> n;

	G = vector<vector<int>>(n);

	for (int i = 0; i < n; ++i) {
		int mi;
		file >> mi;
		for (int j = 0; j < mi; ++j) {
			int eij;
			file >> eij;
			G[i].push_back(eij - 1);
	    }
	}

	file.close();

	print();
	int s = 1;
	int e = 6;
	cout << "G has path between " << s << " and " << e << "?: " << (dijkstra(s - 1, e - 1) ? "yes" : "no") << endl;

    return 0;
}

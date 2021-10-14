#include <iostream>
#include <vector>
#include <stack>

using namespace std;


struct Edge {
	int to, len;

	Edge(int _to, int _len) {
		to = _to;
		len = _len;
	}

	friend ostream &operator << (ostream &out, const Edge& edge) {
		return out << edge.to << " " << edge.len;
	}

};


vector<vector<Edge> > graph;

int dist[1000];

int n, m;

vector<int> st;

void dfs(int start, int end) {
	st.push_back(start);

	if(start == end) {
		cout << "Found Route: " << endl;
		for(int i = 0; i < st.size(); i ++) {
			cout << st[i] << " ";
		}
		cout << endl;
		st.pop_back();
		return;
	}

	for(int i = 0; i < graph[start].size(); i ++) {
		Edge curr = graph[start][i];
		int new_dist = dist[start] + curr.len;

		if(dist[curr.to] == -1 || new_dist < dist[curr.to]) {
			dist[curr.to] = new_dist;
			dfs(curr.to, end);
		}
	}
	st.pop_back();
}


int main() {
	cin >> n >> m;

	graph.resize(n);
	
	for(int i = 0; i < n; i ++) {
		dist[i] = -1;
	}

	for(int i = 0; i < m; i ++) {
		int from, to, len;
		cin >> from >> to >> len;
		graph[from].push_back(Edge(to, len));
		graph[to].push_back(Edge(from, len));
	}
	
	//for(int i = 0; i < n; i ++) {
	//	cout << i << ": " << endl;
	//	for(int j = 0; j < graph[i].size(); j ++) {
	//		cout << graph[i][j] << endl;
	//	}
	//}

	int A, B;
	cin >> A >> B;
	
	dist[A] = 0;
	dfs(A, B);
	
	cout << "Distances: " << endl;
	for(int i = 0; i < n; i ++ ) {
		cout << dist[i] << " " ;
	}
	cout << endl;

	return 0;
}

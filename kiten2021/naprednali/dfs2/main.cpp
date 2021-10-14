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

bool visited[1000];

int n, m;

vector<int> st;

void dfs(int start, int prev) {
	st.push_back(start);

	for(int i = 0; i < graph[start].size(); i ++) {
		Edge curr = graph[start][i];
		int new_dist = visited[start] + curr.len;

		if(!visited[curr.to]) {
			visited[curr.to] = 1;
			dfs(curr.to, start);
		} else if(curr.to != prev) {
			vector<int> loop;
			bool real = false;
			for(int i = st.size() - 1; i > 0; i --) {
				loop.push_back(st[i]);
				if(st[i] == curr.to) {
					real = true;
					break;
				}
			}
			if(real) {
				cout << endl << "LOOP:" << endl;
				for(int i = 0; i < loop.size(); i ++) {
					cout << loop[i];
				}
			}
			cout << endl;
			st.pop_back();
		}
	}
	st.pop_back();
}


int main() {
	cin >> n >> m;

	graph.resize(n);

	for(int i = 0; i < m; i ++) {
		int from, to;
		cin >> from >> to;
		graph[from].push_back(Edge(to, 1));
		graph[to].push_back(Edge(from, 1));
	}

	//for(int i = 0; i < n; i ++) {
	//	cout << i << ": " << endl;
	//	for(int j = 0; j < graph[i].size(); j ++) {
	//		cout << graph[i][j] << endl;
	//	}
	//}


	visited[0] = true;
	dfs(0, -1);

	return 0;
}

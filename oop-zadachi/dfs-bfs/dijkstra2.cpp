#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge {
	int length;
	int end;

	bool operator <(const Edge &other) const {
		return length < other.length;
	}
};

vector<vector<Edge> > graph;

int n;

int dijkstra(int start, int end) {
	
	priority_queue<Edge> q;
	vector<int> distance(n, -1);

	q.push({0, start});
	distance[start] = 0;

	while(!q.empty()) {
		auto curr = q.top();
		q.pop();
		for(int i = 0; i < graph[curr.end].size(); i ++) {
			auto edge = graph[curr.end][i];
			int old_dist = distance[edge.end];
			int new_dist = curr.length + edge.length;
			if(old_dist == -1 || old_dist > new_dist) {
				q.push({new_dist, edge.end});
				distance[edge.end] = new_dist;
			}
		}
	}
	return distance[end];
}

int main() {
	cin >> n;

	graph = vector<vector<Edge> >(n);
	
	cout << dijkstra(0, 0) << endl;

	//input;
}

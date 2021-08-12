#include<iostream>
#include<queue>
using namespace std;

struct lane{
	int id,prod;
	lane(int id, int prod) {
		this->id = id;
		this->prod = prod;
	}
	bool operator < (lane a) const {
		if(prod != a.prod){
			return prod > a.prod;
		}else{
			return id > a.id;
		}
	}
};

priority_queue<lane> lanes;

int** ans;

int main(){
	int n, m, k;
	cin>> n >> k >> m;
	ans = new int*[m];
	for(int i = 0; i < m; i ++)
		ans[i] = new int[n];

	for(int i = 0; i < m; i++){
		lanes.push(lane(i,0));
	}
	for(int i = 0; i < n; i++){
		int products = i % k + 1;
		lane curr = lanes.top();
		lanes.pop();
		curr.prod += products;
		lanes.push(curr);
		ans[curr.id][products-1] ++;
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < k; j++){
			cout << ans[i][j] << " ";
		}
		cout<<endl;
	}
	
	for(int i = 0; i < m; i ++)
		delete [] ans[i];
	delete [] ans;
	return 0;
}


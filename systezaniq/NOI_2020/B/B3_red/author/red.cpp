#include <cstdio>
#include <iostream>

using namespace std;


int main() {
int n,r, i, j, a[300001], ll, rr;
long long ans;
    scanf("%d%d", &n, &r);
    for (i=1; i<=n; i++) scanf("%d", &a[i]);

	ans= 0;
	ll=1; rr=1;
	while (1){
		if (rr<n)
			while (a[rr]-a[ll]<=r) {
				rr++;
				if (rr==n) break;
			}

		while (a[rr]-a[ll]>r){
			ans= ans + (n - rr+1);
			ll++;
		}


		if (a[n]-a[ll]<=r) break;
	}
	cout << ans << endl;

    return 0;
}

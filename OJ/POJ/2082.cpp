#include<iostream>
#include<cstdio>
#define MAX_N 50000

using namespace std;

int w[MAX_N], h[MAX_N];
int L[MAX_N], R[MAX_N];
int st[MAX_N];
int x[MAX_N + 1];
//x[i] --> L
//x[i + 1] --> R
int n;

void solve(){
	int t = 0;
	for(int i = 0; i < n; i++){
		while(t > 0 && h[ st[t - 1] ] >= h[i]) t--;
		L[i] = t == 0 ? 0 : x[ st[t - 1] + 1];
		st[t++] = i;
	}
	t = 0;
	for(int i = n - 1; i >= 0; i--){
		while(t > 0 && h[ st[t - 1] ] >= h[i]) t--;
		R[i] = t == 0 ? x[n] : x[ st[t - 1] ];
		st[t++] = i;
	}
	int res = 0;
	for(int i = 0; i < n; i++){
		res = max(res, (R[i] - L[i]) * h[i]);
	}
	printf("%d\n", res);
}
int main(){
	while(scanf("%d\n", &n) && n != -1){
		x[0] = 0;
		for(int i = 0; i < n; i++){
			scanf("%d %d\n", w + i, h + i);
			if(i > 0) x[i] = x[i - 1] + w[i - 1];	
		}
		x[n] = x[n - 1] + w[n - 1];
		solve();
	}
	return 0;

}

#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 80000

using namespace std;
typedef long long ll;
int N, st[MAX_N], c[MAX_N], res[MAX_N];

void solve(){
	memset(res, 0, sizeof(res));
	int t = 0;
	for(int i = N - 1; i >= 0; i--){
		while(t > 0 && c[ st[t - 1] ] < c[i]){
			res[i] += res[st[--t]] + 1;
		}
		st[t++] = i;
	}
	ll count = 0;
	for(int i = 0; i < N; i++) count += res[i];
	cout<<count<<endl;
}
int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		scanf("%d", c + i);
	}
	solve();
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 100
#define MAX_W 25000

using namespace std;

int n, W;
int C[MAX_N+1];
bool dp[MAX_W+1];

void solve(){
	int H = W / 2;
	memset(dp, 0, sizeof(dp));
	dp[0] = true;
	for(int i = 1; i <= n; i++){
		for(int j = H; j >= C[i]; j--){
			dp[j] |= dp[j-C[i]];
		}
	}
	for(int i = H; i >= 0; i--){
		if(dp[i]){
			printf("%d\n", W - 2 * i);
			return;
		}
	}
}

int main(){
	int m;
	cin>>m;
	while(m--){
		cin>>n;
		W = 0;
		for(int i = 1; i <= n; i++){
			scanf("%d", C+i);
			W += C[i];
		}
		solve();
	}
	return 0;
}


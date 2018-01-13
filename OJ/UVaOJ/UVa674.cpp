#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_W 7489

using namespace std;

int C[] = {0, 1, 5, 10, 25, 50};
const int n = 5;
int W;
int dp[MAX_W+1];

void solve(){
	printf("%d\n", dp[W]);
}
	
void init(){
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = C[i]; j <= MAX_W; j++){
			dp[j] += dp[j-C[i]];
		}
	}
}
int main(){
	init();
	while(cin>>W){
		solve();
	}
	return 0;
}



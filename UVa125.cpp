#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_V 30


using namespace std;

int E, V;
int dp[MAX_V][MAX_V];


void solve(){
	for(int k = 0; k < V; k++){
		for(int j = 0; j < V; j++){
			for(int i = 0; i < V; i++){
				dp[i][j] += dp[i][k] * dp[k][j];
			}
		}
	}
	for(int k = 0; k < V; k++){
		if(dp[k][k] > 0){
			for(int i = 0; i < V; i++){
				for(int j = 0; j < V; j++){
					if(dp[i][k] != 0 && dp[k][j] != 0){
						dp[i][j] = -1;
					}
				}
			}
			dp[k][k] = -1;
		}
	}
	for(int i = 0; i < V; i++){
		for(int j = 0; j < V; j++){
			printf("%d%c", dp[i][j], j == V - 1 ? '\n' : ' ');
		}
	}
}
int main(){
	int c = 0;
	while(scanf("%d", &E) != EOF){
		memset(dp, 0, sizeof(dp));
		V = 0;
		for(int i = 0; i < E; i++){
			int j, k;
			cin>>j>>k;
			dp[j][k]++;
			V = max(V, j);
			V = max(V, k);
		}
		V++;
		printf("matrix for city %d\n", c++);
		solve();
	}
	return 0;
}



#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAX_T 25000
#define MAX_N 100
#define INF  0x3f3f3f3f


using namespace std;

int dp[MAX_T + 1];
int deq[MAX_T + 1];
int deqv[MAX_T + 1];
int C[MAX_N + 1], V[MAX_N + 1];
int N, T, MAX_V;

void solve(){
	int K = T;
	T += MAX_V * MAX_V;

	memset(dp, 0x3f, sizeof(dp));

	dp[0] = 0;
	for(int i = 1; i <= N; i++){
		for(int a = 0; a < V[i]; a++){
			int s = 0, t = 0;
			for(int j = 0; j * V[i] + a <= T; j++){
				int val = dp[j * V[i] + a] - j;
				while(s < t && deqv[t - 1] >= val) t--;
				deq[t] = j;
				deqv[t++] = val;

				dp[j * V[i] + a] = deqv[s] + j;
				if(deq[s] == j - C[i]){
				       	s++;
				}
			}
		}
	}
	for(int i = 1; i <= N; i++){
		for(int j = T - V[i]; j >= K; j--){
			dp[j] = min(dp[j], dp[j + V[i]] + 1);
		}
	}
	printf("%d\n", dp[K] < INF ? dp[K] : -1);
}

int main(){
	MAX_V = 0;
	scanf("%d %d\n", &N, &T);
	for(int i = 0; i < N; i++){
		scanf("%d", V + i + 1);
		MAX_V = max(MAX_V, V[i+1]);
	}
	for(int i = 0; i < N; i++){
		scanf("%d", C + i + 1);
	}
	solve();
	return 0;
}

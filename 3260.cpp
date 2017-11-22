#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAX_T 10000
#define MAX_N 100
#define INF  1E9


using namespace std;

int d[2][MAX_T + 1];
int deq[MAX_T + 1];
int deqv[MAX_T + 1];
int C[MAX_N + 1], V[MAX_N + 1];
int N, T;

void solve(){
	int* dp = d[0], *last = d[1];
	fill(dp, dp + T + 1, INF);
	fill(last, last + T + 1, INF);
	last[0] = 0;

	for(int i = 1; i <= N; i++){
		dp = d[!(i & 1)], last = d[(i & 1)];
		for(int a = 0; a < V[i]; a++){
			int j, s = 0, t = 0;
			for(j = 0; j * V[i] + a <= T; j++){
				int val = last[j * V[i] + a] - j;
				while(s < t && deqv[t - 1] >= val) t--;
				deq[t] = j;
				deqv[t++] = val;

				dp[j * V[i] + a] = deqv[s] + j;
				if(deq[s] == j - C[i]){
				       	s++;
				}
			}
			s = t = 0;
			for(j = j - 1; j >= 0; j--){
				int val = last[j * V[i] + a] + j;
				while(s < t && deqv[t - 1] >= val) t--;
				deq[t] = j;
				deqv[t++] = val;

				dp[j * V[i] + a] = min(dp[j * V[i] + a], deqv[s] - j);
				if(deq[s] == j + C[i]){
					s++;
				}
			}
		}
		for(int j = 0; j <= T; j++){
			printf("dp[%d][%d] = %d\n", i, j, dp[j]);
		}
		printf("\n");
	}
	printf("%d\n", dp[T]);
}

int main(){
	scanf("%d %d\n", &N, &T);
	for(int i = 0; i < N; i++){
		scanf("%d", V + i + 1);
	}
	for(int i = 0; i < N; i++){
		scanf("%d", C + i + 1);
	}
	solve();
	return 0;
}

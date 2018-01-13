#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 10000 + 10
#define INF 0x3f3f3f3f

using namespace std;

int T[MAX_N + 1], F[MAX_N + 1], dp[MAX_N + 1];
int SF[MAX_N + 1], ST[MAX_N + 1];
int N, S;
int deq[MAX_N];

int f(int j, int i){
	return dp[j] + SF[N] * S + ST[j] * (SF[j] - SF[N]) - SF[j] * S + (SF[N] - SF[j]) * ST[i]; 
}
bool check(int j1, int j2, int j3){
	int a1 = SF[N] - SF[j1], b1 = dp[j1] + ST[j1] * (SF[j1] - SF[N]) - SF[j1] * S + SF[N] * S;
	int a2 = SF[N] - SF[j2], b2 = dp[j2] + ST[j2] * (SF[j2] - SF[N]) - SF[j2] * S + SF[N] * S;
	int a3 = SF[N] - SF[j3], b3 = dp[j3] + ST[j3] * (SF[j3] - SF[N]) - SF[j3] * S + SF[N] * S;
//	return a2 * (b1 - b3) + a3 * (b2 - b1) + a1 * (b3 - b2) >= 0;
	return (a2 - a1) * (b3 - b2) >= (b2 - b1) * (a3 - a2);
}
int solve(){
	dp[0] = 0;
	int s = 0, t = 0;
	deq[t++] = 0;


	for(int i = 1; i <= N; i++){
		while(s + 1 < t && f(deq[s], i) >= f(deq[s + 1], i)) s++; //將前端不是最小值的線拿走
		dp[i] = f(deq[s], i);

		while(s + 1 < t && check(deq[t - 2], deq[t - 1], i)) t--;
		deq[t++] = i;
	}
	return dp[N];
}
int main(){
	scanf("%d\n%d\n", &N, &S);
	SF[0] = ST[0] = F[0] = T[0] = 0;
	for(int i = 1; i <= N; i++){
		scanf("%d %d\n", T + i, F + i);
		SF[i] = SF[i - 1] + F[i];
		ST[i] = ST[i - 1] + T[i];
	}
	printf("%d\n", solve());
	return 0;
}


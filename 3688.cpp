#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 10000
#define MAX_M 100000

using namespace std;

int N, M;
int A[MAX_N+1];
int dp[MAX_M];
int v[] = {1, 2, 1, 3};

void solve(){
	memset(dp, 0, sizeof(dp));
	dp[0] = 2;
	for(int i = 1; i <= N; i++){	
		for(int j = M; j >= A[i]; j--){
			if(dp[j-A[i]] > 0){
				dp[j] |= v[dp[j-A[i]]];
			}
		}
	}
	int res = 0;
	for(int i = 1; i <= M; i++){
		res += (dp[i] == 1);
	}
	printf("%d\n", res);
}

int main(){
	while(cin>>N>>M){
		if(!N && !M) break;
		for(int i = 1; i <= N; i++){
			scanf("%d", A+i);
		}
		solve();
	}
	return 0;
}

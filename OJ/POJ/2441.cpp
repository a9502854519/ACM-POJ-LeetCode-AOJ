#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_N 20
#define MAX_M 20
using namespace std;

int dp[2][1<<MAX_M];
vector<int> G[MAX_N+1];
int N, M;

void swap(int** a, int** b){
	int* temp = *a;
	*a = *b;
	*b = temp;
}

int main(){
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; i++){
		int P;
		scanf("%d", &P);
		for(int j = 0; j < P; j++){
			int t;
			scanf("%d", &t);
			G[i].push_back(t-1);
		}
	}
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	int* crt = dp[1];
	int* last = dp[0];
	for(int i = 1; i <= N; i++){
		for(int S = 0; S < (1 << M); S++){
			if(last[S] > 0){
				for(int k = 0; k < G[i].size(); k++){
					int state = 1 << G[i][k];
					if((state & S) == 0){
						crt[state | S] += last[S];
					}
				}
			}
		}
		swap(crt, last);
		fill(crt, crt+(1<<20), 0);
	}
	int res = 0;
	for(int i = 0; i < (1 << M); i++){
		res += last[i];
	}
	printf("%d\n", res);
	return 0;
}
		
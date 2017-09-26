#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 12
#define MAX_M 12
using namespace std;

int N, M;

int corn[MAX_N + 1];
int dp[2][1<<MAX_M];

bool check(int i, int S, int s){
	//確認左右沒有相鄰
	if((s&(s>>1))) return false;
	//確認上下沒有相鄰
	if((S&s)) return false;
	//確認是否有在不能種的地方種玉米
	if(( (corn[i] ^ s) & s)) return false;
	return true;
}
void swap(int* &a, int* &b){
	int* temp = a;
	a = b;
	b = temp;
}
void out(int s){
	for(int i = M-1; i >= 0; i--){
		printf("%d", (s>>i) & 1 ? 1 : 0);
	}
	printf("\n");
}
		
int main(){
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; i++){
		int t = 0;
		for(int j = 0; j < M; j++){
			int a;
			scanf("%d", &a);
			t = (t<<1) | a;
		}
		corn[i] = t;
		//out(corn[i]);
	}
	
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	int* crt = dp[1], *last = dp[0];
	
	for(int i = 1; i <= N; i++){
		for(int S = 0; S < (1<<M); S++){
			if(last[S] > 0){
				for(int state = 0; state < (1 << M); state++){
					if(check(i, S, state)){//確認沒有違規	
						crt[state] += last[S];
					}
				}
			}
		}
		swap(crt, last);
		memset(crt, 0 , (1<<M)*sizeof(int));
	}
	int res = 0;
	
	for(int S = 0; S < (1<<M); S++){
		res += last[S];
	}
	printf("%d\n", res%100000000);
						
						
	return 0;
}
	
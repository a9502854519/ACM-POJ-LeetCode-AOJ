#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_H 20
#define MAX_W 20

using namespace std;

int W, H;
char m[MAX_H+MAX_W-1][MAX_H+MAX_W-1];
int dp[2][MAX_H+MAX_W][MAX_H+MAX_W][MAX_H+MAX_W][MAX_H+MAX_W];

//linear transform equation
//(x, y) --> (x+y, y-x+H-1)

int dfs(int k, int a, int b, int c, int d){//左上~右下
	if(dp[k][a][b][c][d] >= 0){
	       	return dp[k][a][b][c][d];
	}
	
	int S[H*W];
	memset(S, 0, sizeof(S));
	
	for(int i = a + ((a & 1) ^ k); i < c; i += 2){
		for(int j = b; j < d; j++){
			int temp = -1;
			if(m[i][j] == 'L'){//horizontal
				temp = dfs(k, a, b, i, d) ^ dfs(k, i+1, b, c, d);
			}else if(m[i][j] == 'R'){// vertical
				temp = dfs(k, a, b, c, j) ^ dfs(k, a, j+1, c, d);
			}else if(m[i][j] == 'X'){//both of them above
				temp =  dfs(k, a, b, i, j)   ^ dfs(k, a, j+1, i, d) ^
			                dfs(k, i+1, b, c, j) ^ dfs(k, i+1, j+1, c, d);	     
			}
			if(temp >= 0){
				S[temp]++;
			}
		}
		
	}
	for(int i = 0; i < H*W; i++){
		if(S[i] == 0){
			dp[k][a][b][c][d] = i;
			return dp[k][a][b][c][d];
		}
	}
}

void solve(){
	memset(dp, -1, sizeof(dp));
	for(int i = 0; i < H+W-1; i++){
		for(int j = 0; j < H+W-1; j++){
			if(m[i][j] == 0) dp[(i&1)][i][j][i+1][j+1] = 0;//沒格子可以選，必敗
			else dp[(i&1)][i][j][i+1][j+1] = 1;             //只剩一個格子可以選,只能轉移到grundy值為0的狀態,故為1
		}
	}
	int win = dfs(0, 0, 0, H+W-1, H+W-1) ^ dfs(1, 0, 0, H+W-1, H+W-1);
	if(win > 0) printf("WIN\n");
	else    printf("LOSE\n");
}
int main(){
	scanf("%d %d", &H, &W);
	memset(m, 0, sizeof(m));
	char str[21];
	for(int i = 0; i < H; i++){
		scanf("%s", str);
		for(int j = 0; j < W; j++){
			m[i+j][j-i+H-1] = str[j];
		}
	}
	solve();
	return 0;
}


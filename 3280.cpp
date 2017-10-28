/* 考慮如下字串： axxxxxxxxxxx
 * 可以發現，移除左側的a，和在右邊加一個a，
 * 都可以形成一個迴文字串。考慮成本，當然是
 * 選費用最小的操作。
 * 假設dp[i][j]代表將區間[i, j]變成迴文的最
 * 小成本。我們有兩個字元可以操作：第i個和
 * 第j個，如果我們對i下手，則問題就變成計算
 * 把區間[i+1, j]變成迴文的最小成本；反之為
 * [i, j-1]。還要注意一點，如果i和j的字元相
 * 等的話，還要考慮[i+1, j-1]的情況。
 */

#include<iostream>
#include<algorithm>
#include<cstring>
#define MAX_N 26
#define MAX_M 2000

using namespace std;

int cost[MAX_N];
string ID;
int dp[MAX_M][MAX_M];
int N, M;

void solve(){
	for(int i = 0; i < M; i++) dp[i][i] = 0;
	
	for(int k = 1; k < M; k++){
		for(int i = 0; i + k < M; i++){
			int j = i + k;
			
			dp[i][j] = min(dp[i+1][j] + cost[ID[i] - 'a'], dp[i][j-1] + cost[ID[j] - 'a']);
			if(ID[i] == ID[j]) dp[i][j] = min(dp[i][j], dp[i+1][j-1]);
		}
	}
	cout<<dp[0][M-1]<<endl;
}
int main(){
	int add, rm;
	char c;
	cin>>N>>M>>ID;
	for(int i = 0; i < N; i++){
		cin>>c>>add>>rm;
		cost[c - 'a'] = min(add, rm);
	}
	solve();
	return 0;
}
	
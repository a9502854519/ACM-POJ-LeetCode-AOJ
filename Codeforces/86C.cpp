#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAX_N 1000
#define MAX_M 10
#define MAX_STATE 120
#define MAX_LEN 10
#define MOD 1000000009
using namespace std;

vector<string> P;
int n, m;
int dp[MAX_N + 1][MAX_STATE][MAX_LEN + 10];
int nxt[MAX_STATE][4];
char ACGT[] = "ACGT";

bool check(string s, int j){
	while(s.length() > j){
		int k = lower_bound(P.begin(), P.end(), s) - P.begin();
		if(k < P.size() && P[k] == s) return true;
		s = s.substr(1);
	}
	return false;
}
int solve(){
	vector<string> pfx;
	for(int i = 0; i < P.size(); i++){
		for(int j = 0; j <= P[i].length(); j++){
			pfx.push_back(P[i].substr(0, j));
		}
	}
	sort(pfx.begin(), pfx.end());
	sort(P.begin(), P.end());
	pfx.erase(unique(pfx.begin(), pfx.end()), pfx.end());
	int K = pfx.size();

	for(int i = 0; i < K; i++){
		for(int j = 0; j < 4; j++){
			nxt[i][j] = K;
			string s = pfx[i] + ACGT[j];
			int k;
			while(s.length() > 0){
				k = lower_bound(pfx.begin(), pfx.end(), s) - pfx.begin();
				if(k < K && pfx[k] == s){
				       	nxt[i][j] = k;
					break;
				}
				s = s.substr(1);
			}
		}
	}

	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	for(int t = 0; t < n; t++){
		for(int i = 0; i < K; i++){
			for(int j = pfx[i].length(); j >= 0; j--){
				if(dp[t][i][j] > 0){
					for(int k = 0; k < 4; k++){
						int nxt_state = nxt[i][k];
						if(nxt_state < K){
							string s = pfx[i] + ACGT[k];
							if(check(s, j)){
								dp[t + 1][nxt_state][0] = (dp[t + 1][nxt_state][0] + dp[t][i][j]) % MOD;
							}else{
								dp[t + 1][nxt_state][j + 1] = (dp[t + 1][nxt_state][j + 1] + dp[t][i][j]) % MOD;
							}
						}
					}
				}
			}		
		}
	}	
	int res = 0;
	for(int i = 0; i < K; i++){
		res = (res + dp[n][i][0]) % MOD;
	}
	return res;
}
int main(){
	cin>>n>>m;	
	for(int i = 0; i < m; i++){
		string s;
		cin>>s;
		P.push_back(s);
	}
	printf("%d\n", solve());
	return 0;
}

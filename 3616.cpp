/* 假設dp[i]代表從第0到第i個區間，能榨出的最多牛奶
 * 可以很容易地想出：
 * dp[i] = max(dp[j]) + eff(i) for all j which end(j) <= start(i)
 * 這題多了一個休息時間，不過不礙事，把它加到結束時間就好。
 */

#include<iostream>
#include<algorithm>
#include<cstdio>
#define MAX_M 1000
#define MAX_N 1000000

using namespace std;

struct Farmer_John{
	int start, end, eff;
};
Farmer_John Fj[MAX_M];
int dp[MAX_M];
int N,M,R;

bool cmp(const Farmer_John& a, const Farmer_John& b){
	return a.end < b.end;
}
bool ub_cmp(const int& val, const Farmer_John& a){
	return val < a.end;
}
void solve(){
	sort(Fj, Fj + M, cmp);
	dp[0] = Fj[0].eff;
	int res = dp[0];
	
	for(int i = 1; i < M; i++){
		dp[i] = Fj[i].eff;
		Farmer_John* j = upper_bound(Fj, Fj + M, Fj[i].start, ub_cmp);
		
		for(; j - Fj >= 0; j--){
			if(j->end <= Fj[i].start){
				dp[i] = max(dp[i], dp[j - Fj] + Fj[i].eff);
			}
		}
		res = max(res,dp[i]);
	}
	cout<<res<<endl;
}
int main(){
	
	scanf("%d %d %d", &N, &M, &R);
	for(int i = 0; i < M; i++){
		scanf("%d %d %d", &Fj[i].start, &Fj[i].end, &Fj[i].eff);
		Fj[i].end += R;
	}
	solve();
	return 0;
}
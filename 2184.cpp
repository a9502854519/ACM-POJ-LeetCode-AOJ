/* 題目要求TS和TF最大，而且不能為負
　* 也就是說，如果把TS和TF放在一起計
　* 算，就無法保證兩個都一定　>= 0了
　* 所以要把其中一個提出來
 * dp[i][j]  前i個Si總和為j時最大的Fi之和
 * dp[i][j] = max(dp[i-1][j], dp[i-1][j-T[i].first] + T[i].second)
 * 這次因為j有可能是負的，所以要平移
　* 座標，這裡定義j的原點為100000
 */

#include<iostream>
#include<utility>
#include<algorithm>
#define INF 100000000
#define ORIGIN 100000

using namespace std;

int dp[200001];

pair<int, int> T[101];

void solve(){
	fill(dp,dp+200001,-INF);
	dp[ORIGIN] = 0;
	for(int i = 1; i <= N; i++){
		if(T[i].first >= 0){
			for(int j = 100000; j >= -100000; j--){
				if(j-T[i].first + ORIGIN >= 0 && dp[j-T[i].first + ORIGIN] > -INF)
					dp[j + ORIGIN] = max(dp[j + ORIGIN], dp[j-T[i].first + ORIGIN] + T[i].second);
			}
		}else{
			for(int j = -100000; j <= 100000; j++){
				if(j-T[i].first + ORIGIN <= 200000  && dp[j-T[i].first + ORIGIN] > -INF){
					dp[j + ORIGIN] = max(dp[j + ORIGIN], dp[j-T[i].first + ORIGIN] + T[i].second);
				}
			}
		}
	}
	res = 0;
	for(int j=0; j<=100000; j++){
		if(dp[j + ORIGIN] >= 0){
			res = max(res, dp[j + ORIGIN] + j);
		}
	}
	cout<<res<<endl;
}
int main(){
	int N,res,temp;

	cin>>N;
	for(int i=1;i<=N;i++){
		cin>>T[i].first>>T[i].second;
	}	
	solve();
	return 0;
}

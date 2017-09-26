#include<iostream>
#include<utility>
#include<algorithm>
#define INF 100000000
#define ORIGIN 100000
using namespace std;

int dp[200001];
/*
dp[i][j]  前i個Si總和為j時最大的Fi之和
dp[i][j] = max(dp[i-1][j], dp[i-1][j-T[i].first] + T[i].second)
*/
pair<int, int> T[101];
int main(){
	int N,res,temp;

	while(cin>>N){
		for(int i=1;i<=N;i++){
			cin>>T[i].first>>T[i].second;
		}	
		fill(dp,dp+200001,-INF);
		dp[ORIGIN] = 0;
		for(int i=1;i<=N;i++){
			if(T[i].first>=0){
				for(int j=100000;j>=-100000;j--){
					if(j-T[i].first+ORIGIN>=0 && dp[j-T[i].first + ORIGIN] > -INF)
							dp[j + ORIGIN] = max(dp[j + ORIGIN], dp[j-T[i].first + ORIGIN] + T[i].second);
				}
			}else{
				for(int j=-100000;j<=100000;j++){
					if(j-T[i].first+ORIGIN <= 200000  && dp[j-T[i].first+ORIGIN] > -INF){
							dp[j + ORIGIN] = max(dp[j + ORIGIN], dp[j-T[i].first + ORIGIN] + T[i].second);
					}
				}
			}
		}
		res = 0;
		for(int j=0; j<=100000; j++){
			if(dp[j + ORIGIN] >= 0){
				//cout<<"dp("<<j<<")="<<dp[j+ORIGIN]<<endl;
				res = max(res, dp[j + ORIGIN] + j);
			}
		}
		cout<<res<<endl;
	}
	
	return 0;
}
	

#include<iostream>
#include<algorithm>
using namespace std;
struct Farmer_John{
	int start;
	int end;
	int eff;
	bool operator < (const Farmer_John other) const{
		return end < other.end;
	}
};
Farmer_John Fj[1000];
int calc[1000];
int dp[1000];
		
int main(){
	int N,M,R,res,j;
	cin>>N>>M>>R;
	for(int i=0;i<M;i++){
		cin>>Fj[i].start>>Fj[i].end>>Fj[i].eff;
		Fj[i].end+=R;
	}
	sort(Fj, Fj+M);
	for(int i = 0; i < M; i++) calc[i] = Fj[i].end;
	dp[0] = Fj[0].eff;
	res = dp[0];
	for(int i=1; i<M;i++){
		dp[i] = Fj[i].eff;
		j = upper_bound(calc,calc+M,Fj[i].start)-calc-1;
		for(;j>=0; j--){
			if(Fj[i].eff + dp[j] > dp[i]){
				dp[i] = Fj[i].eff+dp[j];
			}
		}
		res = max(res,dp[i]);
	}
	cout<<res<<endl;
	return 0;
}
	
#include<iostream>
#include<algorithm>
using namespace std;
int cost[26];
string ID;
int dp[2000][2000];
int main(){
	int N,M,add,rm,j;
	char c;
	cin>>N>>M>>ID;
	for(int i=0;i<N;i++){
		cin>>c>>add>>rm;
		cost[c-'a'] = min(add,rm);
	}
	for(int k=0;k<M;k++){
		for(int i=0;i+k<M;i++){
			j = i+k;
			if(k==0){
				dp[i][i] = 0;
			}else{
				dp[i][j] = min(dp[i+1][j] + cost[ID[i] - 'a'], dp[i][j-1] + cost[ID[j] - 'a']);
				if(ID[i] == ID[j])
					dp[i][j] = min(dp[i][j], dp[i+1][j-1]);
			}
		}
	}
	cout<<dp[0][M-1]<<endl;
	return 0;
}
	
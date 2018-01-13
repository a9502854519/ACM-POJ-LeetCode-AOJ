#include<iostream>
#include<algorithm>
#include<stack>
#include<vector>
#define INF 1E15
using namespace std;

vector<int> factor;
long long int ans;
void dfs(int n, int i){
	if(n == 1){
		long long int sum = 0;
		for(int j = 0; j < factor.size(); j++){
			sum = sum*10 + factor[j];
		}
		if(sum < ans) ans = sum;
		return;
	}
	for(; i < 10; i++){
		if(n % i == 0){
			factor.push_back(i);
			dfs(n/i, i);
			factor.pop_back();
		}
	}
}
int main(){
	long long int res;
	int C,N;
	cin>>C;
	for(int i = 0; i < C; i++){
		cin>>N;
		if(N / 10 == 0){
			cout<<N<<endl;
		}else{
			ans = INF;
			dfs(N, 2);
			if(ans == INF) cout<<"-1\n";
			else cout<<ans<<endl;
		}
	}
	return 0;
}
		
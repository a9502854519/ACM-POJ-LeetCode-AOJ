#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<unordered_map>

using namespace std;

class Solution {
public:
	int m;
	unordered_map<int, bool> dp[301];
	bool dfs(int state, int total){
		if(total <= 0) return false;//如果總和已經變0或負值，就是輸了
		if(dp[total].find(state) != dp[total].end()){
			return dp[total][state];
		}
		bool result = false;
		for(int i = 1; i <= m && !result; i++){
			if(((1<<i) & state)){
				result |= !dfs(state ^ (1<<i), total - i);
			}
		}
		dp[total][state] = result;
		return result;
	}
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
		if(desiredTotal == 0) return true;
		m = maxChoosableInteger;
		if((m+1)*m/2 < desiredTotal) return false; 
		for(int i = 0; i < 301; i++) dp[i].clear();
		return dfs( (1<<(m+1))-1, desiredTotal);
    }
};


int main(){
	Solution ans;
	int n, t;
	//cin>>n>>t;
	for(int t = 1; t <= 40; t++){
		cout<<10<<" "<<t<<"\n\t";
		cout<<(ans.canIWin(10,t) ? "true\n" : "false\n");
	}
	
	//cout<<(ans.canIWin(5,50) ? "true\n" : "false\n");
	return 0;
}
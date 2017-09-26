#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<ctime>
#include<vector>
#define INF 1E7
using namespace std;

vector<string> data;
int dp[15][1<<15];
int last[15][1<<15];
int cost[15][15];
int n;

bool check(int i){
	for(int j = 0; j < data.size(); j++){
		if(i != j && data[i].size() < data[j].size()){
			for(int k = 0; k < data[j].size() - data[i].size() + 1; k++){
				if(data[i] == data[j].substr(k, k+data[i].size())) return true;
			}
		}
	}
	return false;
}
int calc(string str1, string str2){
	int res = str2.size();
	for(int i = 1; i <= str1.size() && i <= str2.size(); i++){
		if(str1.substr(str1.size()-i, str1.size()) == str2.substr(0, i)){
			res = str2.size() - i;
		}
	}
	return res;
}
string get(int i, int S){
	string res = "";
	//printf("last[%d][%d] = %d\n", i , S, last[i][S]);
	if(last[i][S] == i){
		res = data[i];
	}else{
		string t = data[i];
		res = get(last[i][S], S^(1<<i));
		string str = data[i];
		for(int i = 1; i <= str.size() && i <= res.size(); i++){
			if(res.substr(res.size()-i, res.size()) == str.substr(0, i)){
				t = str.substr(i, str.size());
				
			}
		}
		res += t;
	}
	return res;
}
string find(string str1, string str2){
	for(int i = 0; i < str1.size(); i++){
		if(str1[i] < str2[i]){
			return str1;
		}else if (str1[i] > str2[i]){
			return str2;
		}
	}
	return str1;
}
int find(int i, int Si, int j, int Sj){
	if(Si == 0){
		return 2;
	}
	string t = find(data[i], data[j]);
	int k = find(last[i][Si], Si^(1<<i), last[j][Sj], Sj^(1<<j));
	if(k == 2){
		if(i == j) return 2;
		else if (t == data[i]) return 0;
		else return 1;
	}
	return k;
}
	
	
int main(){
	int s;
	cin>>s;
	for(int c = 1; c <= s; c++){
		data.clear();
		cin>>n;
		for(int i = 0; i < n; i++){
			string t;
			fill(dp[i], dp[i]+(1<<15), INF);
			cin>>t;
			data.push_back(t);
		}	
		for(int i = 0; i < data.size(); i++){
			if(check(i)){
				data.erase(data.begin()+i);
				i--;
			}
		}
		/*for(int i = 0; i < data.size(); i++){
			cout<<data[i]<<endl;
		}*/
		for(int i = 0; i < data.size(); i++){
			dp[i][1<<i] = data[i].size();
			last[i][1<<i] = i;
			for(int j = 0; j < data.size(); j++){
				if(i != j){
					cost[i][j] = calc(data[i], data[j]);
					
				}else{
					cost[i][j] = 0;
				}
				//printf("cost[%d][%d] = %d\n", i, j, cost[i][j]);
			}
		}
		n = data.size();
		for(int S = 1; S < (1<<n); S++){
			for(int i = 0; i < n; i++){
				if(( S&(1<<i) )){
					for(int j = 0; j < n; j++){
						if(i != j){
							if(dp[i][S] > dp[j][S^(1<<i)] + cost[j][i]){
								dp[i][S] = dp[j][S^(1<<i)] + cost[j][i];
								last[i][S] = j;
							}else if(dp[i][S] == dp[j][S^(1<<i)] + cost[j][i]){
								if(find(last[i][S], S^(1<<i), j, S^(1<<i)) == 1){
									last[i][S] = j;
								}
							}
						}
					}
				}
			}
		}
		string res = "";
		int length = INF;
		int S = (1<<n) - 1;
		int k;
		for(int i = 0; i < n; i++){
			if(length > dp[i][S]){
				length = dp[i][S];
				res = get(i, S);
			}else if(length == dp[i][S]){
				string t = get(i, S);
				res = find(res, t);//比較字典順序
			}
		}
		if(c > 1) printf("\n\n");
		printf("Scenario #%d:\n", c);
		cout<<res;
	}
	return 0;
}
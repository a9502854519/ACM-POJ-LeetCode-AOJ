#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> d;
int n;
/*
	終止條件：當有任一個點無法消耗完它的度數時(即度數比它小的點數量小於它的度數)，即代表無法形成圖。
*/
void solve(){
	sort(d.begin(), d.end());
	int n = d.size() - 1;
	for(int i = n; i >= 0; i--){
		int degree = d.back();
		d.pop_back();
		if(degree != 0){
			for(int j = 0; j < degree; j++){
				if(d.size() < degree || d[d.size() - 1 - j] == 0){
					cout<<"Not possible\n";
					return;
				}else{
					d[d.size() - 1 - j]--;
				}
			}
			sort(d.begin(), d.end());
		}else{
			break;
		}
	}
	cout<<"Possible\n";
}
int main(){
	while(cin>>n){
		if(n == 0) break;
		d.clear();
		for(int i = 0; i < n; i++){
			int temp;
			cin>>temp;
			d.push_back(temp);
		}
		solve();
	}
	return 0;
}
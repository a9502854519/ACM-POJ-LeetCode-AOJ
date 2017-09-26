#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

int main(){
	long long int n;
	vector< vector<int> > ans;
	while(cin>>n){
		ans.clear();
		long long int sum = 1, s = 1, t = 2;
		while(t > s){
			if(sum < n){
				sum += t*t;
				t++;
			}else{
				if(sum == n){
					vector<int> temp;
					for(int i = s; i < t; i++) temp.push_back(i);
					ans.push_back(temp);
				}
				sum -= s*s;
				s++;
			}
		}
		printf("%d\n",ans.size());
		for(int i = 0; i < ans.size(); i++){
			printf("%d ", ans[i].size());
			for(int j = 0; j < ans[i].size(); j++) printf("%d ", ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}
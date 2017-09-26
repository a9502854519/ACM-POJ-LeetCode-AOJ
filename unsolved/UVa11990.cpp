#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#define MAX_n 200000
using namespace std;

int n, m;
int bit[MAX_n + 1];
int per[MAX_n];
vector< vector<int> > box;
int sum(int i){
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}
void add(int i, int v){
	while(i <= n){
		bit[i] += v;
		i += i & -i;
	}
}
int sum(int i, int j){
		return sum(j) - sum(i-1);
}
int main(){
	while(cin>>n>>m){
		int res = 0;
		memset(bit, 0, sizeof(bit));
		memset(per, 0, sizeof(per));
		box.clear();
		for(int i = 0; i < n; i++){
			scanf("%d", per+i);
			res += sum(per[i]+1, n);
			add(per[i], 1);
		}
		//分箱法
		int b = sqrt(n); // 一個箱子的元素數量
		for(int i = 0;i < n;){
			vector<int> temp;
			while(temp.size() < b && i < n){
				temp.push_back(per[i++]);
			}
			sort(temp.begin(), temp.end());
			box.push_back(temp);
		}

		int r;
		while(m--){
			cin>>r;
			
			printf("%d\n", res);
			
			bool redline = false;
			vector<int>::iterator it;
			
			for(int i = 0; i < box.size(); i++){
				if(redline == false){
					//找比r大的
					it = lower_bound(box[i].begin(), box[i].end(), r);
					if(*it != r || it == box[i].end()) res -= (box[i].end() - it);
					else{
						//逐一計算大於和小於r的個數
						int count = 0;
						bool k = false;
						
						for(int j = i*b; j < i*b+b && j < n; j++){
							if(per[j] == r){
								k = true;
								per[j] = -1;
							}
							if((k == false && per[j] > r) || (k == true && per[j] < r && per[j] > 0)) count++;
						}
						res -= count;
						redline = true;
						box[i].erase(it);
					}
				}else{
					//找比r小的
					it = upper_bound(box[i].begin(), box[i].end(), r);
					res -= (it - box[i].begin());
				}
				
				
			}
		}
	}
	return 0;
}
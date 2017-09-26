#include<iostream>
#include<cstdio>
#include<algorithm>
#include<utility>
#include<vector>
#include<queue>
#define INF 100000000
using namespace std;
typedef pair<int, int> pp;
pair<int, int> time[25001];
bool cmp(const pair<int, int>&p, const pair<int, int>& q){
	if(p.first!=q.first) return p.first<q.first;
	return p.second<q.second;
}

int main(){
	int N,T,res,end,last,i,highest;
	priority_queue<int> q;
	while(true){
		scanf("%d%d",&N,&T);
		for(i=0;i<N;i++)
			scanf("%d%d",&time[i].first, &time[i].second);
		sort(time,time+N, cmp);
		
		i=0;
		do i++; while(time[i].first == 1);
		highest = time[i-1].second;
		res = 1;
		if(time[i-1].first == 1){
			while(i<N){
				for(;i<N;i++){
					if(time[i].first <= highest+1)
						q.push(time[i].second);
					else
						break;
				}
				if(!q.empty()){
					if(highest < q.top()){
						highest = q.top();
						res ++;
					}
				}
				else break;
				while(!q.empty()) q.pop();
			}
		}
		printf("%d\n", highest < T ? -1 : res);
	}
		
	
	return 0;	
}
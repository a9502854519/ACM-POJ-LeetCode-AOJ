#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define MAX_N 500
using namespace std;

int N, M;
int del_pt;
int num;
int dfn[MAX_N];
int low[MAX_N];
bool arti_pt;
struct edge{
	int to;
};
vector<edge> G[MAX_N];
void bicon(int u, int v){ //從u到v
	dfn[v] = low[v] = ++num;
	for(int i = 0; i < G[v].size(); i++){ //依序查看跟v連接的點
		int to = G[v][i].to;
		if(to != del_pt){
			if(dfn[to] < 0){ //還沒造訪過
				bicon(v, to);
				low[v] = min(low[v], low[to]);
				if(low[to] >= dfn[v] && dfn[v] != low[v]){
					arti_pt = true;
				}
			}else if(to != u){ 
				low[v] = min(low[v], dfn[to]);
			}
		}
	}
}
		
		
void solve(){
	if(N < 2){
		cout<<"NO\n";
		return;
	}
	for(int i = 0; i < N;i++){
		del_pt = i; //枚舉刪點
		num = 0;
		arti_pt = false;
		memset(dfn, -1, sizeof(dfn));
		memset(low, -1, sizeof(low));
		bicon(-1, del_pt == 0 ? 1 : 0); //強連通圖建立
		if(arti_pt){
			printf("NO\n");
			return;
		}else{
			int count = 0;
			for(int j = 0; j < N; j++){
				if(j != del_pt && (dfn[j] < 0 || (dfn[j] == low[j] && ++count >= 2))){
					printf("NO\n");
					return;
				}
			}
		}
	}
	
	printf("YES\n");
}
void init(){
	for(int i = 0; i < N; i++){
		G[i].clear();
	}
}
int main(){
	while(scanf("%d%d", &N, &M)){
		if(N == 0 && M == 0) break;
		init();
		while(M--){
			int a, b;
			scanf("%d%d", &a, &b);
			G[a].push_back((edge){b});
			G[b].push_back((edge){a});
		}
		solve();
	}
}
			
			
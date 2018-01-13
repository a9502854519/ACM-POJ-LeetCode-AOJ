#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
#define MAX_V 500
#define INF 1000000000
using namespace std;


vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];
int n, V;

void add_edge(int u, int v){
	G[u].push_back(v);
}
bool dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w)){
			//如果u已經配對過的話，就試著幫它的配對點w找另外一個配對點。如果找得到的話，就將v和u配對。
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}
int bipartite_matching(){
	int res = 0;
	memset(match, -1, sizeof(match));
	for(int v = 0; v < V; v++){
		if(match[v] < 0){
			memset(used, 0, sizeof(used));
			if(dfs(v)){
				res++;
			}
		}
	}
	return res;
}
		
void init(){
	for(int i = 0; i < MAX_V; i++) G[i].clear();
	V = n;
}
int main(){
	
	while(cin>>n){
		init();
		char str[100];
		int v, m, a, s = 0, t = n+1;
		for(int i = 0; i < n; i++){
			scanf("%d: (%d)",&v, &m);
			while(m--){
				scanf("%d", &a);
				add_edge(i, a);
			}
		}
		printf("%d\n", n - bipartite_matching());
	}
	return 0;
}
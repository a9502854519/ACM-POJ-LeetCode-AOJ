#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define MAX_V 400

using namespace std;

int Girl, Boy, V, E;
vector<int> G[MAX_V+1];
int adj[MAX_V+1][MAX_V+1];
int match[MAX_V+1];
bool used[MAX_V+1];

void init(){
	for(int i = 0; i <= MAX_V; i++){
		G[i].clear();
		fill(adj[i], adj[i]+MAX_V+1, 1);
	}
}
void add_edge(){
	for(int i = 1; i <= Girl; i++){
		for(int j = Girl+1; j <= V; j++){
			if(adj[i][j]){
				G[i].push_back(j);
				G[j].push_back(i);
			}
		}
	}
}
bool dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w)){
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}

int bipartite_matching(){
	int res = 0;
	memset(match, -1, sizeof(match));
	for(int v = 1; v <= V; v++){
		if(match[v] < 0){
			memset(used, 0, sizeof(used));
			if(dfs(v)){
				res++;
			}
		}
	}
	return res;
}
	

int main(){
	for(int c = 1;; c++){
		cin>>Girl>>Boy>>E;
		if(!Girl && !Boy && !E) break;
		init();
		V = Girl+Boy;
		while(E--){
			int g, b;
			scanf("%d%d", &g, &b);
			b += Girl;
			adj[g][b] = 0;
			adj[b][g] = 0;
		}
		add_edge();
		printf("Case %d: %d\n",c, V -bipartite_matching());
	}
	return 0;
}
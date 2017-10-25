#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_V 199

using namespace std;


int V, E;
vector<int> G[MAX_V];
bool used[MAX_V];
int color[MAX_V];

void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}

bool dfs(int v, int c){
	used[v] = true;
	color[v] = c;
	for(int i = 0; i < G[v].size(); i++){
		if(!used[G[v][i]]){
		       if(!dfs(G[v][i], c ^ 1)) return false;
		}else{
			if(c == color[G[v][i]])	return false;
		}
	}
	return true;
}
bool solve(){
	memset(used, 0, sizeof(used));
	memset(color, -1, sizeof(color));
	for(int v = 0; v < V; v++){
		if(!used[v]){
			if(!dfs(v, 0)) return false;
		}
	}
	return true;
}
void init(){
	for(int i = 0; i < MAX_V; i++){
		G[i].clear();
	}
}
int main(){
	while(cin>>V && V){
		init();
		cin>>E;
		for(int i = 0; i < E; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			add_edge(u, v);
		}
		printf("%s\n", solve() ? "BICOLORABLE." : "NOT BICOLORABLE.");
	}
	return 0;
}


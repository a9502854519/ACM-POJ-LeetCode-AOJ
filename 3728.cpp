#include<iostream>
#include<algorithm>
#include<stack>
#include<cstdio>
#include<vector>
#define MAX_V 50000
#define MAX_LOG_V 16
#define INF 1E9

using namespace std;


int V, Q, root;
vector<int> G[MAX_V];
int depth[MAX_V];
int parent[MAX_LOG_V][MAX_V];
int max_w[MAX_LOG_V][MAX_V];
int min_w[MAX_LOG_V][MAX_V];
int up_profit[MAX_LOG_V][MAX_V];
int down_profit[MAX_LOG_V][MAX_V];
int w[MAX_V];


void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
void dfs(int p, int v, int d){
	//---
	parent[0][v] = p;
	min_w[0][v] = max_w[0][v] = w[v];
	up_profit[0][v] = down_profit[0][v] = 0;
	if(p != -1){
		min_w[0][v] = min(w[p], w[v]);
		max_w[0][v] = max(w[p], w[v]);
		up_profit[0][v] = (w[p] - w[v] > 0 ? w[p] - w[v] : 0);
		down_profit[0][v] = (w[v] - w[p] > 0 ? w[v] - w[p] : 0);
	}
	depth[v] = d;
	//---
	for(int i = 0; i < G[v].size(); i++){
		if(G[v][i] != p){
			dfs(v, G[v][i], d + 1);
		}
	}
}
void init(){
	root = 0;
	dfs(-1, root, 0);
	for(int k = 0; k < MAX_LOG_V - 1; k++){
		for(int v = 0; v < V; v++){
			if(parent[k][v] < 0){
			    parent[k+1][v] = -1;
				max_w[k+1][v] = max_w[k][v];
				min_w[k+1][v] = min_w[k][v];
				up_profit[k+1][v] = up_profit[k][v];
				down_profit[k+1][v] = down_profit[k][v];
			}else{
			    parent[k+1][v] = parent[k][parent[k][v]];
				max_w[k+1][v] = max(max_w[k][v], max_w[k][parent[k][v]]);
				min_w[k+1][v] = min(min_w[k][v], min_w[k][parent[k][v]]);
				up_profit[k+1][v] = max( max(up_profit[k][v], up_profit[k][parent[k][v]]), 
						          max_w[k][parent[k][v]] - min_w[k][v]);
				down_profit[k+1][v] = max( max(down_profit[k][v], down_profit[k][parent[k][v]]),
						          max_w[k][v] - min_w[k][parent[k][v]]);
			}
		}
	}
}

void solve(){
	init();
	int u, v;
	scanf("%d", &Q);
	while(Q--){
		scanf("%d %d", &u, &v);
		u--; v--;
		int res = -INF, lmn = w[u], lmx = w[u], rmn = w[v], rmx = w[v], lca;

		if(depth[u] > depth[v]){
			for(int k = 0; k < MAX_LOG_V; k++){
				if((depth[u] - depth[v]) >> k & 1){
					lmx = max_w[k][u];
					res = max(res, max(lmx - lmn, up_profit[k][u]));
					lmn = min(lmn, min_w[k][u]);
					u = parent[k][u];
				}
			}
		}else if(depth[u] < depth[v]){
			for(int k = 0; k < MAX_LOG_V; k++){
				if((depth[v] - depth[u]) >> k & 1){
					rmn = min_w[k][v];
					res = max(res, max(down_profit[k][v], rmx - rmn));
					rmx = max(rmx, max_w[k][v]);
					v = parent[k][v];
				}
			}
		}
		if(u == v) lca = u;
		else{
			for(int k = MAX_LOG_V - 1; k >= 0; k--){
				if(parent[k][u] != parent[k][v]){
					lmx = max_w[k][u];
					rmn = min_w[k][v];
					res = max(max(up_profit[k][u], down_profit[k][v]), res);
					res = max(res, max(lmx - lmn, rmx - rmn));
					lmn = min(lmn, min_w[k][u]);
					rmx = max(rmx, max_w[k][v]);
					u = parent[k][u];
					v = parent[k][v];
				}
			}
			lca = parent[0][u];
		}
		lmn = min(lmn, w[lca]);
		rmx = max(rmx, w[lca]);
		res = max(res, rmx - lmn);
		printf("%d\n", res);
	}
}
int main(){
	scanf("%d", &V);
	for(int i = 0; i < V; i++){
		scanf("%d", w + i);
	}
	for(int i = 0 ; i < V - 1; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		add_edge(u - 1, v - 1);
	}
	solve();
	return 0;
}



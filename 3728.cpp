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
int max_profit[MAX_LOG_V][MAX_V];
int min_profit[MAX_LOG_V][MAX_V];
int w[MAX_V];


void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
void dfs(int p, int v, int d){
	//---
	parent[0][v] = p;
	min_w[0][v] = (p == -1 ? w[v] : min(w[v], w[p]));
	max_w[0][v] = (p == -1 ? w[v] : max(w[v], w[p]));
	if(p == -1 || w[p] - w[v] <= 0) max_profit[0][v] = 0;
	else max_profit[0][v] = w[p] - w[v];

	if(p == -1 || w[p] - w[v] >= 0) min_profit[0][v] = 0;
	else min_profit[0][v] = w[p] - w[v];

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
				max_profit[k+1][v] = max_profit[k][v];
				min_profit[k+1][v] = min_profit[k][v];
			}else{
			    parent[k+1][v] = parent[k][parent[k][v]];
				max_w[k+1][v] = max(max_w[k][v], max_w[k][parent[k][v]]);
				min_w[k+1][v] = min(min_w[k][v], min_w[k][parent[k][v]]);
				max_profit[k+1][v] = max( max(max_profit[k][v], max_profit[k][parent[k][v]]), 
						          max_w[k][parent[k][v]] - min_w[k][v]);
				min_profit[k+1][v] = min( min(min_profit[k][v], min_profit[k][parent[k][v]]),
						          min_w[k][parent[k][v]] - max_w[k][v]);
/*				if(k == 0 && v + 1 == 2){
					printf("min_profit[%d][%d] = %d\n", k+1, v+1, min_profit[k+1][v]);
					printf("min_profit[%d][%d] = %d\n", k, v+1, min_profit[k][v]);
					printf("min_profit[%d][%d] = %d\n", k, parent[k][v]+1, min_profit[k][parent[k][v]]);
					printf("min_w[%d][%d] = %d\n", k, parent[k][v]+1, min_w[k][parent[k][v]]);
					printf("max_w[%d][%d] = %d\n", k, v+1, max_w[k][v]);
				}
*/			}
		}
	}
}

void solve(){
	init();
	int u, v;
	scanf("%d", &Q);
	//for(int k = 0; k < MAX_LOG_V; k++){
	//	for(int v = 0; v < V; v++){
	//		printf("min_w[%d][%d] = %d\n", k, v+1, min_w[k][v]);
	//	}
	//}
	while(Q--){
		scanf("%d %d", &u, &v);
		u--; v--;
		int res = -INF, mn = w[u], mx = w[v], lca;

		if(depth[u] > depth[v]){
			for(int k = 0; k < MAX_LOG_V; k++){
				if((depth[u] - depth[v]) >> k & 1){
					res = max(res, max_profit[k][u]);
					mn = min(mn, min_w[k][u]);
					u = parent[k][u];
				}
			}
		}else if(depth[u] < depth[v]){
			for(int k = 0; k < MAX_LOG_V; k++){
				if((depth[v] - depth[u]) >> k & 1){
					res = max(res, -min_profit[k][v]);
					mx = max(mx, max_w[k][v]);
					v = parent[k][v];
				}
			}
		}
		if(u == v) lca = u;
		else{
			for(int k = MAX_LOG_V - 1; k >= 0; k--){
				if(parent[k][u] != parent[k][v]){
					res = max(max(max_profit[k][u], -min_profit[k][v]), res);
					mn = min(mn, min_w[k][u]);
					mx = max(mx, max_w[k][v]);
					u = parent[k][u];
					v = parent[k][v];
				}
			}
			lca = parent[0][u];
		}
		mn = min(mn, w[lca]);
		mx = max(mx, w[lca]);
		res = max(res, mx - mn);
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



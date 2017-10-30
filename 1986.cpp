#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_V 40000
#define MAX_E 40000
#define MAX_LOG_V 16
#define INF 1E9

using namespace std;

struct edge{
	int to, cost;
	edge() {}
	edge(int to, int cost) : to(to), cost(cost) {}
};

int V, E;
vector<edge> G[MAX_V];
int root;
int parent[MAX_LOG_V][MAX_V];

int sum[MAX_V * 2 - 1];
int depth[MAX_V];
int id[MAX_V];

void add_edge(int u, int v, int cost){
	G[u].push_back(edge(v, cost));
	G[v].push_back(edge(u, cost));
}
void dfs(int v, int p, int d, int& k){
	id[v] = k++;

	parent[0][v] = p;
	depth[v] = d;

	for(int i = 0; i < G[v].size(); i++){
		if(G[v][i].to != p){
			sum[k] = sum[k-1] + G[v][i].cost;
			dfs(G[v][i].to, v, d+1, k);
			sum[k] = sum[k-1] - G[v][i].cost;
			k++;
		}
	}
}
void init(){
	int k = 0;
	memset(sum, 0, sizeof(sum));
	dfs(root, -1, 0, k);
	for(int k = 0; k < MAX_LOG_V - 1; k++){
		for(int v = 0; v < V; v++){
			if(parent[k][v] < 0) parent[k+1][v] = -1;
			else parent[k+1][v] = parent[k][parent[k][v]];
		}
	}
}
void swap(int &a, int& b){
	a ^= b;
	b ^= a;
	a ^= b;
}
int lca(int u, int v){
	if(depth[u] > depth[v]) swap(u, v);
	for(int k = 0; k < MAX_LOG_V; k++){
		if((depth[v] - depth[u]) >> k & 1){
			v = parent[k][v];
		}
	}
	if(u == v) return u;
	for(int k = MAX_LOG_V - 1; k >= 0; k--){
		if(parent[k][u] != parent[k][v]){
			u = parent[k][u];
			v = parent[k][v];
		}
	}
	return parent[0][u];
}


void solve(){
	root = 0;
	init();	
	int K;
	cin>>K;
/*	for(int i = 0; i < 2 * V - 1; i++){
		printf("%d ", sum[i]);
	}
	cout<<endl;
*/	while(K--){
		int u, v;
		scanf("%d %d", &u, &v);
		int L = lca(u-1, v-1);
		printf("%d\n", sum[id[u-1]] + sum[id[v-1]] - 2 * sum[id[L]]);
	}
}
int main(){
	scanf("%d %d", &V, &E);
	for(int i = 0; i < E; i++){
		int u, v, cost;
		char c;
		scanf("%d %d %d %c", &u, &v, &cost, &c);
		add_edge(u - 1, v - 1, cost);
	}
	solve();
}

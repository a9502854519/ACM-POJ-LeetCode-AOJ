#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX_V 30


using namespace std;

int E, V;
vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];
int dp[MAX_V][MAX_V];

void add_edge(int from, int to){
	G[from].push_back(to);
	rG[to].push_back(from);
}

void dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		if(!used[G[v][i]]) dfs(G[v][i]);
	}
	vs.push_back(v);
}

void rdfs(int v, int k, int& count){
	used[v] = true;
	cmp[v] = k;
	for(int i = 0; i < rG[v].size(); i++){
		if(!used[rG[v][i]]) rdfs(rG[v][i], k, ++count);
	}
	if(count > 1) dp[v][v] = -1;
}

int scc(){
	memset(used, 0, sizeof(used));
	vs.clear();

	for(int v = 0; v < V; v++){
		if(!used[v]) dfs(v);
	}
	memset(used, 0, sizeof(used));
	int k = 0;
	for(int i = vs.size() - 1; i >= 0; i--){
		int count = 1;
		if(!used[vs[i]]) rdfs(vs[i], k++, count);
	}
	return k;
}

void calc(int i, int u, bool cycle){
	if(dp[u][u] == -1) used[u] = true;
	for(int j = 0; j < G[u].size(); j++){
		int v = G[u][j];
		if(!used[v] && dp[i][v] != -1){
			if(cycle || dp[v][v] == -1) dp[i][v] = -1;
			else dp[i][v]++;
			calc(i, v, (dp[v][v] == -1 || cycle));
		}
	}
}

void solve(){
	scc();
	for(int i = 0; i < V; i++){
		memset(used, 0, sizeof(used));
		calc(i, i, (dp[i][i] == -1));
	}
	for(int i = 0; i < V; i++){
		for(int j = 0; j < V; j++){
			printf("%d%c", dp[i][j], j == V - 1 ? '\n' : ' ');
		}
	}
}

void init(){
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < MAX_V; i++){
		G[i].clear();
		rG[i].clear();
	}
}	
int main(){
	int c = 0;
	while(scanf("%d", &E) != EOF){
		V = 0;
		init();
		for(int i = 0; i < E; i++){
			int j, k;
			cin>>j>>k;
			add_edge(j, k);
			V = max(V, j);
			V = max(V, k);
		}
		V++;
		printf("matrix for city %d\n", c++);
		solve();
	}
	return 0;
}



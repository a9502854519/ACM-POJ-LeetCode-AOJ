#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_V 10000

using namespace std;

int V, E;
vector<int> G[MAX_V];     //鄰接表
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];
int cmp_count[MAX_V];

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
void rdfs(int v, int k){
	used[v] = true;
	cmp[v] = k;
	cmp_count[k]++;
	for(int i = 0; i < rG[v].size(); i++){
		if(!used[rG[v][i]]) rdfs(rG[v][i], k);
	}
}
int scc(){
	memset(cmp_count, 0, sizeof(cmp_count));
	memset(used, 0, sizeof(used));
	vs.clear();
	for(int v = 0; v < V; v++){
		if(!used[v]) dfs(v);
	}
	memset(used, 0, sizeof(used));
	int k = 0;
	for(int i = vs.size() - 1; i >= 0; i--){
		if(!used[vs[i]]) rdfs(vs[i], k++);
	}
//	for(int v = 0; v < V; v++){
//		printf("cmp[%d] = %d\n", v+1, cmp[v]);
//	}
	int res = 0;
	for(int i = 0; i < V; i++){
		if(cmp_count[i] > 1) res++;
	}
	return res;
}
void solve(){
	printf("%d\n", scc());
}
int main(){
	scanf("%d %d", &V, &E);
	for(int i = 0; i < E; i++){
		int A, B;
		scanf("%d %d", &A, &B);
		add_edge(A-1, B-1);
	}
	solve();
	return 0;
}



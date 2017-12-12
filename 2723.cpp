#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_N 4096
#define MAX_M 2048

using namespace std;

struct vertex{
	int v, k;
	vertex() {}
	vertex(int v, int k) : v(v), k(k) {}
};
vector<vertex> G[MAX_N];
vector<vertex> rG[MAX_N];
vector<int> vs;
bool used[MAX_N];
int cmp[MAX_N];
int N, M;

void add_edge(int u, int v, int k){
	G[u].push_back(vertex(v, k));
	rG[v].push_back(vertex(u, k));
}
void dfs(int v, int x){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		if(G[v][i].k <= x && !used[G[v][i].v]) dfs(G[v][i].v, x);
	}
	vs.push_back(v);
}
void rdfs(int v, int x, int k){
	used[v] = true;
	cmp[v] = k;
	for(int i = 0; i < rG[v].size(); i++){
		if(rG[v][i].k <= x && !used[rG[v][i].v]) rdfs(rG[v][i].v, x, k);
	}
}
int scc(int x){
	memset(used, 0, sizeof(used));
	for(int i = 0; i < N; i++){
		if(!used[i]) dfs(i, x);
	}
	
	memset(used, 0, sizeof(used));
	int k = 0;
	for(int i = vs.size() - 1; i >= 0; i--){
		if(!used[vs[i]]) rdfs(vs[i], x, k++);
	}
	return k;
}
bool C(int x){
	N *= 2;
	scc(x);
	N /= 2;
	for(int i = 0; i < N; i++){
		if(cmp[i] == cmp[i + N]) return false;
	}
	return true;
}
int solve(){
	int ub = M + 1, lb = 0, mid;
	while(ub - lb > 1){
		mid = (lb + ub) / 2;
		if(C(mid)) lb = mid;
		else ub = mid;
	}
	return lb;
}
void init(){
	for(int i = 0; i < 2 * N; i++){
		G[i].clear();
		rG[i].clear();
	}
}
int main(){
	while(cin>>N>>M && (N || M)){
		N *= 2;
		init();
		for(int i = 0; i < N / 2; i++){
			int a, b;
			scanf("%d %d\n", &a, &b);
			add_edge(a, b + N, 0);
			add_edge(b, a + N, 0);
		}
		for(int i = 1; i <= M; i++){
			int a, b;
			scanf("%d %d\n", &a, &b);
			add_edge(a + N, b, i);
			add_edge(b + N, a, i);
		}
		printf("%d\n", solve());
	}
	return 0;
}
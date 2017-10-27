#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAX_V 100

using namespace std;

vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V],  V;
int in[MAX_V], out[MAX_V];


void add_edge(int from, int to){
	G[from].push_back(to);
	rG[to].push_back(from);
}
void dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		if(!used[G[v][i]]){
		       	dfs(G[v][i]);
		}
	}
	vs.push_back(v);
}

void rdfs(int v, int k){
	used[v] = true;
	cmp[v] = k;
	for(int i = 0; i < rG[v].size(); i++){
		if(!used[rG[v][i]]){
		       	rdfs(rG[v][i], k);
		}
	}
}
int scc(){
	memset(used, 0, sizeof(used));
	vs.clear();
	for(int v = 0; v < V; v++){
		if(!used[v]){
		       	dfs(v);
		}
	}

	memset(used, 0, sizeof(used));
	int k = 0;
	for(int i = vs.size() - 1; i >= 0; i--){
		if(!used[vs[i]]){
		       	rdfs(vs[i], k++);
		}
	}
	return k;
}

void solve(){
	int k = scc();
	if(k == 1){
		printf("1\n0\n");
		return;
	}
	for(int v = 0; v < V; v++){
		for(int i = 0; i < G[v].size(); i++){
			if(cmp[v] != cmp[ G[v][i] ]){
				in[ cmp[ G[v][i] ] ]++;
				out[ cmp[v] ]++;
			}
		}
	}
	int in_count = 0, out_count = 0;
	for(int i = 0; i < k; i++){
		if(in[i] == 0) in_count++;
		if(out[i] == 0) out_count++;
	}
	printf("%d\n%d\n", in_count, max(in_count, out_count));
}
	
int main(){
	scanf("%d", &V);
	for(int i = 0; i < V; i++){
		int a;
		while(true){
			scanf("%d", &a);
			if(!a) break;
			add_edge(i, a-1);
		}
	}
	solve();
	return 0;
}

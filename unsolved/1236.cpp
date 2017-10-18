#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#define MAX_V 100

using namespace std;

vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> sccG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V],  V;
int scc_parent[MAX_V];

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
		}else if(cmp[rG[v][i]] != k){
//			printf("(%d, %d)\n", v+1, rG[v][i]+1);
			scc_parent[k] = cmp[rG[v][i]];
//			printf("The parent of %d is %d\n", k, scc_parent[k]);
			sccG[cmp[rG[v][i]]].push_back(k);
		}
	}
}
int leaf_count, root_count;
void scc_dfs(int v, int root){
	used[v] = true;
	bool leaf = true;
	for(int i = 0; i < sccG[v].size(); i++){
		if(!used[sccG[v][i]]){
			scc_dfs(sccG[v][i], root);
			leaf = false;
		}
	}
	if(leaf && v != root){
		leaf_count++;
	}
}
void solve(){
	memset(used, 0, sizeof(used));
	vs.clear();
	for(int v = 0; v < V; v++){
		if(!used[v]){
		       	dfs(v);
		}
	}
	memset(used, 0, sizeof(used));
	int k = 0;
	for(int i = 0; i < V; i++){
		scc_parent[i] = i;
	}
	for(int i = vs.size() - 1; i >= 0; i--){
		if(!used[vs[i]]){
		       	rdfs(vs[i], k++);
		}
	}
//	cout<<endl;
//	for(int i = 0; i < k; i++){
//		printf("The parent of %d is %d\n", i, scc_parent[i]);
//	}
	leaf_count = 0, root_count = 0;
	memset(used, 0, sizeof(used));
	for(int i = 0; i < k; i++){
		if(scc_parent[i] == i){
			root_count++;
			scc_dfs(i, i);
		}
	}
//	printf("root : %d\nleaf : %d\n", root_count, leaf_count);
	printf("%d\n%d\n", root_count, leaf_count + (root_count > 1 ? root_count : 0));
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

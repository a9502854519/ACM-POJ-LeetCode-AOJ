#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#define MAX_V 100

using namespace std;

vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
bool leaf[MAX_V];
int cmp[MAX_V],  V;
int root[MAX_V];

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
void scc_dfs(int r, int v, int scc_v){
	used[v] = true;
	leaf[scc_v] = true;
	root[v] = r;
	for(int i = 0; i < G[v].size(); i++){
		if(cmp[G[v][i]] != scc_v) leaf[scc_v] = false;
		if(!used[G[v][i]]){
			scc_dfs(r, G[v][i], cmp[G[v][i]]);
		}
	}
}
int calc(){
	memset(used, 0, sizeof(used));
	memset(leaf, 0, sizeof(leaf));
	memset(root, -1, sizeof(root));
	int count = 0;
	for(int i = vs.size() - 1; i >= 0; i--){
		if(!used[vs[i]]){
			count++;
			scc_dfs(vs[i], vs[i], cmp[vs[i]]);
		}
	}
	return count;
}
void solve(){
	int k;
	int edge_add = 0;
	int root_count;
	bool update;
	
		k = scc();
		root_count = calc();
		//
//		for(int i = 0; i < V; i++){
//			printf("cmp[%d] =  %d   root[%d] = %d\n", i+1, cmp[i], i+1, root[i]+1);
//		}
		//
		
		for(int i = 0; i < k; i++){
			if(leaf[i]){
//				printf("i = %d\n", i);
				for(int j = 0; j < V; j++){
					if(cmp[j] == i){ //j屬於第i個分量，而且j不是自成一點
						if(cmp[j] != cmp[ root[j] ])	edge_add++;
						break;
					}
				}
			}
		}

//	printf("edge_add = %d   root_count = %d\n", edge_add, root_count);
	if(edge_add > 0 && root_count > edge_add) edge_add = root_count;
	printf("%d\n%d\n",root_count, edge_add);	
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

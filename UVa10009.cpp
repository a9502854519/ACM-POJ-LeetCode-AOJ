#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX_V 26
#define MAX_LOG_V 5

using namespace std;

int V, E, root;
int T[MAX_V]; //城市-->編號
char v[MAX_V];//編號-->城市 
vector<int> G[MAX_V];
int parent[MAX_LOG_V][MAX_V];
int depth[MAX_V];

void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
void dfs(int u, int p, int d){
	parent[0][u] = p;
	depth[u] = d;
	for(int i = 0; i < G[u].size(); i++){
		if(G[u][i] != p) dfs(G[u][i], u, d+1);
	}
}
void init(){
	dfs(root, -1, 0);
	for(int k = 0; k + 1 < MAX_LOG_V; k++){
		for(int v = 0; v < V; v++){
			if(parent[k][v] < 0) parent[k+1][v] = -1;
			else parent[k+1][v] = parent[k][parent[k][v]];
		}
	}
}
void swap(int& u, int& v){
	u ^= v;
	v  = u ^ v;
	u ^= v;
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
		
void solve(int v1, int v2){
	int p = lca(v1, v2);
	vector<char> res;
	if(v1 != p){
		do{
			printf("%c", v[v1]);
			v1 = parent[0][v1];
		}while(p != v1);
	}
	printf("%c", v[p]);
	if(v2 != p){
		do{
			res.push_back(v[v2]);
			v2 = parent[0][v2];
		}while(v2 != p);
	}
	for(int i = res.size() - 1; i >= 0; i--){
		printf("%c", res[i]);
	}
	printf("\n");

}
void reset(){
	memset(T, -1, sizeof(T));
	memset(v, -1, sizeof(v));
	for(int i = 0 ; i < MAX_V; i++) G[i].clear();
	V = 0;
}

int main(){
	int C, n;
	cin>>C;
	while(C--){
		reset();
		string str1, str2;
		scanf("%d %d", &E, &n);
		for(int i = 0; i < E; i++){
			cin>>str1>>str2;	
			int t1 = str1[0] - 'A', t2 = str2[0] - 'A';
			if(T[t1] == -1) T[t1] = V++;
			if(T[t2] == -1) T[t2] = V++;

			int v1 = T[t1], v2 = T[t2];
			if(v[v1] == -1) v[v1] = str1[0];
			if(v[v2] == -1) v[v2] = str2[0];
			add_edge(v1, v2);
			if(str1[0] == 'R') root = v1;
		}
		init();
		while(n--){
			cin>>str1>>str2;
			int t1 = str1[0] - 'A', t2 = str2[0] - 'A';
			solve(T[t1], T[t2]);
		}
		if(C > 0) printf("\n");
	}
	return 0;
}



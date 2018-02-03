#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAX_V 2000
#define INF 1000000000
using namespace std;

int N, M, L, V;

struct vertex{
	int v, time;
	bool operator < (const vertex& other){
		return time < other.time;
	}
}data[MAX_V];
int d[100][100];

vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void init(){
	memset(d, -1, sizeof(d));
	for(int i = 0; i < V; i++) G[i].clear();
}
void floyd_warshall(){
	for(int k = 0; k < N; k++){
		
		for(int i = 0; i < N; i++){
			d[i][i] = 0;
			for(int j = 0; j < N; j++){
				if(d[i][j] < 0) d[i][j] = INF;
				d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
			}
		}
	}
}

void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
bool dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w)){
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int bipartite_matching(){
	int res = 0;
	memset(match, -1, sizeof(match));
	for(int v = 0; v < V; v++){
		if(match[v] < 0){
			memset(used, 0, sizeof(used));
			if(dfs(v)){
				res++;
			}
		}
	}
	return res;
}
int main(){
	int count = 0;
	while(cin>>N>>M>>L){
		if(!N && !M && !L) break;
		V = L;
		init();
		while(M--){
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			d[a][b] = c; 
			d[b][a] = c;
		}
		for(int i = 0; i < V; i++){
			scanf("%d%d", &data[i].v, &data[i].time);
		}
		floyd_warshall();
		/* 
		   左半部的編號為0~V-1
		   右半部對應的編號為V ~ 2V-1
		*/
		for(int i = 0; i < V; i++){
			for(int j = 0; j < V; j++){
				int u = data[i].v, v = data[j].v;
				if(i != j && data[i].time+d[u][v] <= data[j].time){
					add_edge(i, j+V);
				//	printf("u = %d, v = %d\n",u, v);
				}
			}
		}
		printf("%d\n", V - bipartite_matching());	
	}
	return 0;
}
			
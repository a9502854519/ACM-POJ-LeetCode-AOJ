#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<cstring>
#define INF 1000000000
#define MAX_V 2*50*50+1

using namespace std;
typedef pair<int, int> P;

struct edge{
	int to, cap, cost, rev;
};
int N, K, V;
int mat[50][50];
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost){
	edge e;
	e.to = to, e.cap = cap, e.cost = cost, e.rev = G[to].size();
	G[from].push_back(e);
	e.to = from, e.cap = 0, e.cost = -cost, e.rev = G[from].size()-1;
	G[to].push_back(e);
}

int min_cost_flow(int s, int t, int f){
	int res = 0;
	while(f > 0){
		//Bellman-Ford
		fill(dist, dist+V, INF);
		dist[s] = 0;
		bool update = true;
		while(update){
			update = false;
			for(int v = 0; v < V; v++){
				if(dist[v] == INF) continue;
				for(int i = 0; i < G[v].size(); i++){
					edge &e = G[v][i];
					if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
						dist[e.to] = dist[v] + e.cost;
						prevv[e.to] = v;
						preve[e.to] = i;
						update = true;
					}
				}
			}
		}
		if(dist[t] == INF){
			return -1;
		}
		int d = f;
		for(int v = t; v != s; v = prevv[v]){
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += dist[t];
		for(int v = t; v != s; v = prevv[v]){
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
			//e.cost = 0;
		}
	}
	return res;
}

int main(){
	cin>>N>>K;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &mat[i][j]);
		}
	}
	V = 2*N*N+1;
	int s = 0, t = V-1;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			int u = i*N+j+1;
			add_edge(u, u+N*N, 1, -mat[i][j]);
			add_edge(u, u+N*N, INF, 0);
			if(i < N-1){
				add_edge(u+N*N, u+N, INF, 0);
			}
			if(j < N-1){
				add_edge(u+N*N, u+1, INF, 0);
			}
				
		}
	}
	add_edge(s, 1, INF, 0);
	printf("%d\n", -min_cost_flow(s, t, K));
	return 0;
}
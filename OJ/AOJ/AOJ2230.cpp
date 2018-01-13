#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<cstring>
#define INF 1000000000
#define MAX_V 101
#define inf 1000000

using namespace std;
typedef pair<int, int> P;

struct edge{
	int to, cap, cost, rev;
	edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};
int N, M, V;
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost){
	G[from].push_back(edge(to, cap, cost, G[to].size()));
	G[to].push_back(edge(from, 0, -cost, G[from].size()-1));
}

int min_cost_flow(int s, int t){
	int res = 0;
	int f = INF;
	do{
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
		}
	}while(dist[t] < 0);
	return res;
}

int main(){
	cin>>N>>M;
	V = N+1;
	for(int i = 0; i < M; i++){
		int x, y, s;
		cin>>x>>y>>s;
		add_edge(x, y, INF, -s);
		add_edge(x, y, 1, -s-inf);
	}
	//longest path from 0 to N-1
	//Bellman-Ford
	fill(dist, dist+V, INF);
	dist[0] = 0;
	bool update = true;
	while(update){
		update = false;
		for(int v = 0; v < V-1; v++){
			if(dist[v] == INF) continue;
			for(int i = 0; i < G[v].size(); i++){
				edge &e = G[v][i];
				if(e.cap > 1 && dist[e.to] > dist[v] + e.cost){
					dist[e.to] = dist[v] + e.cost;
					prevv[e.to] = v;
					preve[e.to] = i;
					update = true;
				}
			}
		}
	}
	int D = -dist[N-1];
	add_edge(N-1, N, INF, D);
	cout<<min_cost_flow(0, N)+M*inf<<endl;
	return 0;
}
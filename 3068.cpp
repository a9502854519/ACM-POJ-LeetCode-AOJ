#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<cstring>
#define INF 1000000000
#define MAX_V 64*2

using namespace std;
typedef pair<int, int> P;

struct edge{
	int to, cap, cost, rev;
};
int N, M, V;
vector<edge> G[MAX_V];//0~V-1為輸入點，V~2V-1為輸出點
int dist[MAX_V];
int h[MAX_V];
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
	memset(h, 0, sizeof(h));
	while(f > 0){
		//Dijkstra
		priority_queue< P, vector<P>, greater<P> > q;
		fill(dist, dist+V, INF);
		dist[s] = 0;
		q.push(P(dist[s], s));
		while(!q.empty()){
			P p = q.top(); q.pop();
			int v = p.second;
			if(dist[v] < p.first) continue;
			for(int i = 0; i < G[v].size(); i++){
				edge &e = G[v][i];
				if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
					dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
					prevv[e.to] = v;
					preve[e.to] = i;
					q.push(P(dist[e.to], e.to));
				}
			}
		}
		if(dist[t] == INF){
			return -1;
		}
		for(int v = 0; v < V; v++) h[v] += dist[v];
		
		int d = f;
		for(int v = t; v != s; v = prevv[v]){
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += d * h[t];
		for(int v = t; v != s; v = prevv[v]){
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}
		

void init(){
	for(int i = 0; i < V; i++) G[i].clear();
}
int main(){
	for(int c = 0;;c++){
		cin>>N>>M;
		if(!N && !M)	break;
		V = 2*N;
		init();
		while(M--){
			int i, j, v;
			scanf("%d%d%d", &i, &j, &v);
			add_edge(i+N, j, 1, v);
		}
		for(int i = 1; i < N-1; i++) add_edge(i, i+N, 1, 0);
		add_edge(0, 0+N, 2, 0);
		add_edge(N-1, 2*N-1, 1, 0);
		int res = min_cost_flow(0, N-1, 2);
		printf("Instance #%d: ", c+1);
		if(res < 0) printf("Not possible\n");
		else printf("%d\n", res);
	}
	return 0;
}
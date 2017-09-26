#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
#include<cstring>
#define INF 1000000000
#define MAX_V 100*100+2
using namespace std;
typedef pair<int, int> P;


int N, M, V;
struct point{
	int x, y;
};
struct edge{
	int to, cap, cost, rev;
};
vector<edge> G[MAX_V];
vector<point> House;
vector<point> Man;
int h[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost){
	G[from].push_back((edge){to, cap, cost, G[to].size()});
	G[to].push_back((edge){from, 0, -cost, G[from].size()-1});
}
void init(){
	House.clear();
	Man.clear();
	for(int i = 0; i < MAX_V; i++) G[i].clear();
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
int main(){
	char str[101];
	while(cin>>N>>M){
		if(!N && !M) break;
		
		init();
		for(int i = 0; i < N; i++){
			scanf("%s", str);
			for(int j = 0; j < M; j++){
				if(str[j] == 'H') House.push_back((point){i, j});
				else if (str[j] == 'm') Man.push_back((point){i, j});
			}
		}
		V = House.size() + Man.size() + 2;
		int s = 0, t = V-1;
		for(int i = 0; i < House.size(); i++){
			add_edge(s, i+1, 1, 0);
			for(int j = 0; j < Man.size(); j++){
				add_edge(i+1, j+House.size()+1, 1, abs(House[i].x - Man[j].x) + abs(House[i].y - Man[j].y));
				if(i == 0) add_edge(j+House.size()+1, t, 1, 0);
			}
		}
		printf("%d\n", min_cost_flow(s, t, House.size()));
				
	}
	return 0;
}
		
	
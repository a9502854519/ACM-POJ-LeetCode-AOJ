#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#define MAX_N 200
#define MAX_M 200
#define MAX_V 402
#define INF 1000000000
using namespace std;

struct edge{
	int to, cap, rev;
};
vector<edge> G[MAX_V+1];//0為源點，1~m為stall，m+1~m+n為牛，m+n+1為匯點
int level[MAX_V+1];
int iter[MAX_V+1];
int N, M;

void add_edge(int from, int to, int cap){
	edge e;
	e.to = to, e.cap = cap, e.rev = G[to].size();
	G[from].push_back(e);
	e.to = from, e.cap = 0, e.rev = G[from].size()-1;
	G[to].push_back(e);
}
void bfs(int s){
	memset(level, -1, sizeof(level));
	queue<int> q;
	level[s] = 0;
	q.push(s);
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); i++){
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				q.push(e.to);
			}
		}
	}
}
int dfs(int v, int t, int f){
	if(v == t) return f;
	for(int &i = iter[v]; i < G[v].size(); i++){
		edge &e = G[v][i];
		if(e.cap > 0 && level[v] < level[e.to]){
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
				e.cap -=d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}
int max_flow(int s, int t){
	int flow = 0;
	while(true){
		bfs(s);
		if(level[t] < 0) return flow;
		memset(iter, 0, sizeof(iter));
		int f;
		while((f = dfs(s, t, INF)) > 0){
			flow += f;
		}
	}
}
void init(){
	for(int i = 0; i <= MAX_V; i++) G[i].clear();
}
int main(){
	while(cin>>N>>M){
		init();
		for(int i = 1; i <= N; i++){
			int s, stall;
			scanf("%d", &s);
			while(s--){
				scanf("%d", &stall);
				add_edge(M+i, stall, 1);
			}
		}
		for(int i = M+1; i <= M+N; i++){
			add_edge(0, i, 1);
		}
		for(int i = 1; i <= M; i++){
			add_edge(i, N+M+1, 1);
		}
		printf("%d\n", max_flow(0, N+M+1));
	}
	return 0;
}
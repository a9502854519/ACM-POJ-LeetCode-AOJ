#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define INF 1E9
#define MAX_V 3000

using namespace std;

struct edge{
	int to, cap, rev;
	edge() {}
	edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};
int N, M, V, E;
vector<edge> G[MAX_V];
vector<edge> Copy_G[MAX_V];
int level[MAX_V];
int iter[MAX_V];


void add_edge(int from, int to, int cap){
	G[from].push_back(edge(to, cap, G[to].size()));
	G[to].push_back(edge(from, 0, G[from].size()-1));
}
void bfs(int s){
	memset(level, -1, sizeof(level));
	queue<int> q;
	level[s] = 0;
	q.push(s);
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); i++){
			edge& e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				q.push(e.to);
			}
		}
	}
}
int dfs(int v, int t, int f){
	if(v == t) return f;
	for(int& i = iter[v]; i < G[v].size(); i++){
		edge& e = G[v][i];
		if(e.cap > 0 && level[v] < level[e.to]){
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
				e.cap -= d;
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
	for(int i = 0; i < V; i++) G[i].clear();
}



bool C(int x){
	int  s = 0, t = M+N+1;
	for(int i = 0; i < V; i++) G[i] = Copy_G[i];
	for(int i = 0; i < G[t].size(); i++){
		edge& e = G[t][i];
		G[e.to][e.rev].cap = x;
	}
	return max_flow(s, t) == N;
}
void solve(){
	int ub = N, lb = 0, mid;
	while(ub - lb > 1){
		mid = (ub + lb) / 2;
		if(C(mid)) ub = mid;
		else       lb = mid;
	}
	printf("%d\n", ub);
}
int main(){
	//1~M:群組的編號
	//M+1~M+N:人的編號
	//s:0, t:M+N+1
	while(cin>>N>>M){
		if(!N && !M) break;
		V = M+N+2;
		init();
		int s = 0, t = M+N+1;
		for(int i = 1; i <= N; i++){
			char str[20];
			scanf("%s", str);
			char a;
			while(true){
				scanf("%c", &a);
				if(a == '\n') break;
				add_edge(M+i, (int)(a-'0')+1, 1);
			}
		}
		for(int i = M+1; i <= M+N; i++){
			add_edge(s, i, 1);
		}
		for(int i = 1; i <= M; i++){
			add_edge(i, t, 0);
		}
		for(int i = 0; i < V; i++) Copy_G[i] = G[i];
		solve();
	}
	return 0;
}
			


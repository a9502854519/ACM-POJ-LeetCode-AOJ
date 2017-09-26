#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#define INF 1000000000
#define MAX_V 54

using namespace std;

int n, V;
struct edge{
	int to, cap, rev;
};
vector<edge> G[MAX_V];//1~n為投影片，n+1 ~ n+n為編號
int level[MAX_V];
int iter[MAX_V];

void init(){
	for(int i = 0; i < MAX_V; i++) G[i].clear();
}
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
void reset(){
	int s = 0, t = 2*n+1;
	for(int i = 0; i < G[s].size(); i++){
		edge &e = G[s][i];
		e.cap = 1, G[e.to][e.rev].cap = 0;
	}
	for(int i = 1; i <= n ;i++){
		for(int j = 0; j < G[i].size(); j++){
			edge &e = G[i][j];
			if(e.to != s){
				e.cap = 1, G[e.to][e.rev].cap = 0;
			}
		}
	}
	for(int i = 0; i < G[t].size(); i++){
		edge &e = G[t][i];
		e.cap = 0, G[e.to][e.rev].cap = 1;
	}
}
void solve(){
	int s = 0, t = 2*n+1;
	edge* res[27];
	for(int i = 1; i <= n; i++){
		add_edge(s, i, 1);
		add_edge(n+i, t, 1);
	}
	int f = max_flow(s, t);
	for(int v = 1; v <= n; v++){
		for(int i = 0; i < G[v].size(); i++){
			edge &e = G[v][i];
			if(e.cap == 0){
				res[v] = &e;
				break;
			}
		}
	}
	//唯一匹配判斷
	bool matched[27];
	int count = 0;
	memset(matched, true, sizeof(matched));
	for(int v = 1; v <= n; v++){
		reset();
		res[v]->cap = 0;
		if((f = max_flow(s, t)) == n){
			matched[v] = false;
			count++;
		}
	}
	if(count == n){
		printf("none\n");
		return;
	}
	for(int v = 1; v <= n; v++){
		if(matched[v]){
			printf("(%c,%d) ",(char)(v+64), (res[v]->to)-n);
		}
	}
	printf("\n");
}
int main(){
	int data[27][4];
	for(int c = 1;;c++){
		cin>>n;
		if(n == 0) break;
		init();
		for(int i = 1; i <= n; i++){
			scanf("%d%d%d%d\n", &data[i][0], &data[i][1], &data[i][2], &data[i][3]);
		}
		for(int i = 1; i <= n; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			for(int j = 1; j <= n; j++){
				int x1 = data[j][0], x2 = data[j][1], y1 = data[j][2], y2 = data[j][3];
				if(x1 <= x && x <= x2 && y1 <= y && y <= y2){
					add_edge(j, n+i, 1);
				}
			}
		}
		V = 2*n+2;
		printf("Heap %d\n", c);
		solve();
		printf("\n");
	}
	return 0;
}
			
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#include<cmath>
#include<algorithm>
#define MAX_V 1102
#define EPS 1E-5
#define INF 1000000000

using namespace std;

struct edge{
	int to, rev;
	double cap;
};
vector<edge> G[MAX_V];//0為s，1~n為點，n+1~n+m為邊，n+m+1為t
int level[MAX_V];
int iter[MAX_V];
int n, m;
int visited[MAX_V];
void add_edge(int from, int to, double cap){
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
			if(e.cap > 0+EPS && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				q.push(e.to);
			}
		}
	}
}

double dfs(int v, int t, double f){
	if(v == t){
		return f;
	}
	for(int &i = iter[v]; i < G[v].size(); i++){
		edge &e = G[v][i];
		if(e.cap > 0 + EPS && level[v] < level[e.to]){
			double d = dfs(e.to, t, min(f, e.cap));
			if(d > 0 + EPS){
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

double max_flow(int s, int t){
	double flow = 0;
	while(true){
		bfs(s);
		if(level[t] < 0){
			return flow;
		}
		memset(iter, 0, sizeof(iter));
		double f;
		
		while(true){
			if((f = dfs(s, t, INF)) > 0 + EPS){
				flow += f;
			}else{
				break;
			}
		}
	}
	return flow;
}
void init(double g){
	for(int v = n+1; v <= n+m; v++){
		for(int i = 0; i < G[v].size(); i++){
			edge &e = G[v][i];
			e.cap = INF; G[e.to][e.rev].cap = 0;
		}
	}
	for(int i = 0; i < m; i++){
		edge &e = G[0][i];
		e.cap = 1; G[e.to][e.rev].cap = 0;
	}
	for(int i = 0; i < n; i++){
		edge &e = G[n+m+1][i];
		e.cap = 0; G[e.to][e.rev].cap = g;
	}
}
double C(double g){
	
	init(g);
	double d = max_flow(0, n+m+1);
	double w = (double)m - d;
	return  w <= 0+1e-8;
}
vector<int> res;
void min_cut(int s){
	if(s >= 1 && s <= n) res.push_back(s);
	visited[s] = 1;
	for(int i = 0; i < G[s].size(); i++){
		edge e = G[s][i];
		if(!visited[e.to] && e.cap > 0){
			min_cut(e.to);
		}
	}
}
void min_cut(void){
	memset(visited, 0, sizeof(visited));
	min_cut(0);
}
int main(){
	cin>>n>>m;
	for(int i = 1; i <= m; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		add_edge(n+i, a, INF);
		add_edge(n+i, b, INF);
		add_edge(0, n+i, 1);
	}
	for(int i = 1; i <= n; i++){
		add_edge(i, n+m+1, 0);
	}
	double ub = (double)m, lb = (double)1/n, mid;
	for(int i = 0; i < 100; i++){
		mid = (ub + lb)/2;
		if(C(mid)) ub = mid;
		else lb = mid;
	}
	min_cut();
	sort(res.begin(), res.end());
	if(res.size() > 0){
		printf("%d\n", res.size());
		for(int i = 0; i < res.size(); i++){
			printf("%d\n", res[i]);
		}
	}else{
		printf("1\n1\n");
	}
	return 0;
}
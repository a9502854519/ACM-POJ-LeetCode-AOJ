#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define MAX_V 100 + 10
#define MAX_E 1000
#define INF 1E9
#define EPS 1E-10

using namespace std;

struct edge{
	int to, rev;
	double cap;
	edge() {}
	edge(int to, double cap, int rev) : to(to), cap(cap), rev(rev) {}
};
int V, E;
vector<edge> G[MAX_V];
vector<edge> bG[MAX_V];
int level[MAX_V];
int iter[MAX_V];
int degree[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to){
	G[from].push_back(edge(to, 1, G[to].size()));
	G[to].push_back(edge(from, 1, G[from].size() - 1));
}
void add_edge(int from, int to, double cap){
	G[from].push_back(edge(to, cap, G[to].size()));
	G[to].push_back(edge(from, 0, G[from].size() - 1));
}
void bfs(int s){
	memset(level, -1, sizeof(level));
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while(!que.empty()){
		int v = que.front(); que.pop();
		for(int i = 0; i < G[v].size(); i++){
			edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0){
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}
double dfs(int v, int t, double f){
	if(v == t) return f;
	for(int &i = iter[v]; i < G[v].size(); i++){
		edge &e = G[v][i];
		if(e.cap > 0 && level[v] < level[e.to]){
			double d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
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
	for(;;){
		bfs(s);
		if(level[t] < 0) break;
		memset(iter, 0, sizeof(iter));
		double f;
		while((f = dfs(s, t, INF)) > 0){
			flow += f;
		}
	}
	return flow;
}
double h(double g){
	int s = 0, t = V + 1;
	G[s].clear(); G[t].clear();
	for(int i = 1; i <= V; i++){
		G[i].assign(bG[i].begin(), bG[i].end());
		add_edge(s, i, E);
		add_edge(i, t, E + 2 * g - degree[i]);
	}
	double f = max_flow(s, t);
	// for(int i = 0; i < V + 2; i++){
		// printf("%d : \n", i);
		// for(int j = 0; j < G[i].size(); j++){
			// printf("\tto = %d  cap = %lf\n", G[i][j].to, G[i][j].cap);
		// }
	// }
	
	// cout << (E * V - f) / 2 << endl;
	// printf("f = %lf\n--------------------\n\n\n", f);
	return (E * V - f) / 2;
}
void find(int v, vector<int>& res){
	res.push_back(v);
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		edge &e = G[v][i];
		if(!used[e.to] && e.cap > 0) find(e.to, res);
	}
}
void solve(){
	for(int i = 1; i <= V; i++){
		bG[i].assign(G[i].begin(), G[i].end());
	}
	double n = V, m = E, ub = m, lb = 1 / (n + 1), mid;
	vector<int> res;
	while(ub - lb > 1 / (n * n)){
		mid = (ub + lb) / 2;
		if(h(mid) < 1E-5){
			ub = mid;
		}else{
			lb = mid;
		}
	}
	if(E == 0) cout << "1\n1\n";
	else{
		h(lb);
		res.clear();
		find(0, res);
		sort(res.begin(), res.end());

		cout << res.size() - 1 << endl;
		for(int i = 1; i < res.size(); i++) printf("%d\n", res[i]);
	}
}
int main(){
	memset(degree, 0, sizeof(degree));
	cin >> V >> E;
	for(int i = 0; i < E; i++){
		int a, b;
		scanf("%d %d\n", &a, &b);
		add_edge(a, b);
		degree[a]++;
		degree[b]++;
	}
	solve();
	return 0;
}
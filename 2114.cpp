#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<utility>
#include<algorithm>
#define MAX_N 10000
#define MAX_M 100
#define INF 1e9

using namespace std;

struct edge{
	int to, cost;
	edge() {}
	edge(int to, int cost) : to(to), cost(cost) {}
};
vector<edge> G[MAX_N];
bool centroid[MAX_N];
int subtree_size[MAX_N];
int N, M;
int ans[MAX_M];
int query[MAX_M];
bool exist[MAX_M];

void add_edge(int u, int v, int cost){
	G[u].push_back(edge(v, cost));
	G[v].push_back(edge(u, cost));
}
int compute_subtree_size(int v, int p){
	int c = 1;
	for(int i = 0; i < G[v].size(); i++){
		int w = G[v][i].to;
		if(w != p && !centroid[w]){
			c += compute_subtree_size(w, v);
		}
	}
	subtree_size[v] = c;
	return c;
}
pair<int, int> search_centroid(int v, int p, int t){
	pair<int, int> res = make_pair(INF, -1);
	int s = 1, m = 0;

	for(int i = 0; i < G[v].size(); i++){
		int w = G[v][i].to;
		if(w != p && !centroid[w]){
			res = min(res, search_centroid(w, v, t));
			m = max(m, subtree_size[w]);
			s += subtree_size[w];
		}

	}
	m = max(m, t - s);
	res = min(res, make_pair(m, v));
	return res;
}
void enumerate_path(int v, int p, int cost, vector<int>& ds){
	ds.push_back(cost);
	for(int i = 0; i < G[v].size(); i++){
		int w = G[v][i].to;
		if(w != p && !centroid[w]){
			enumerate_path(w, v, cost + G[v][i].cost, ds);
		}
	}
}
int count_pair(vector<int>& ds, int d){
	int res = 0, i = 0, j = ds.size() - 1;
	sort(ds.begin(), ds.end());
	for(int i = 0; ds[i] < d && i < ds.size(); i++){
		res += upper_bound(ds.begin() + i + 1, ds.end(), d - ds[i]) - 
			lower_bound(ds.begin() + i + 1, ds.end(), d - ds[i]);
	}
			
	return res;
}
void solve_subproblem(int v){
	compute_subtree_size(v, -1);
	int s = search_centroid(v, -1, subtree_size[v]).second;
	centroid[s] = true;
	
	for(int i = 0; i < G[s].size(); i++){
		if(!centroid[G[s][i].to]){
			solve_subproblem(G[s][i].to);
		}
	}
	
	vector<int> ds;
	ds.push_back(0);
	for(int i = 0; i < G[s].size(); i++){
		if(!centroid[G[s][i].to]){
			vector<int> tds;
			enumerate_path(G[s][i].to, s, G[s][i].cost, tds);
			for(int k = 0; k < M; k++){
				ans[k] -= count_pair(tds, query[k]);
			}
			ds.insert(ds.end(), tds.begin(), tds.end());
		}
	}
	for(int k = 0; k < M; k++){
		ans[k] += count_pair(ds, query[k]);
	}
	centroid[s] = false;
}
void solve(){
	memset(ans, 0, sizeof(ans));
	solve_subproblem(0);
	for(int i = 0; i < M; i++){
		printf("%s\n", ans[i] > 0 ? "AYE" : "NAY");
	}
	printf(".\n");
}
void init(){
	for(int i = 0; i < N; i++) G[i].clear();
	memset(exist, false, sizeof(exist));
}
int main(){
	while(cin>>N && N > 0){
		init();
		for(int i = 0; i < N; i++){
			int d, c;
			while(scanf("%d", &d) && d > 0){
				scanf("%d", &c);
				add_edge(i, d - 1, c);
			}
		}
		int q;
		M = 0;
		while(cin>>q && q > 0){
			query[M++] = q;
		}
		solve();
	}
	return 0;
}

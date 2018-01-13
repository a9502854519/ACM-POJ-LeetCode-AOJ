#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#define MAX_V 5002 //加入s 和 t
#define INF 1000000000
using namespace std;
typedef long long  ll;

int n, m;

struct edge{
	int to;
	ll cap;
	int rev;
};
vector<edge> G[MAX_V];
int level[MAX_V]; //分層圖
int iter[MAX_V]; // iter[v] 表示點v目前調查到哪條邊，之前調查過的就不需要再調查了，因為一定沒有路可以走。

void add_edge(int from, int to, ll cap){
	edge e; 
	e.to = to, e.cap = cap, e.rev = G[to].size();
	G[from].push_back(e);
	e.to = from, e.cap = 0, e.rev = G[from].size() - 1;
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

ll dfs(int v, int t, ll f){
	if(v == t) return f;
	for(int &i = iter[v]; i < G[v].size(); i++){
		edge &e = G[v][i];
		if(e.cap > 0 && level[v] < level[e.to]){
			ll d = dfs(e.to, t, min(f, e.cap));
			if(d > 0){
				if(e.cap < INF) e.cap -= d; //容量無限的邊不用扣除
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

ll max_flow(int s, int t){
	ll flow = 0;
	while(true){
		bfs(s);
		if(level[t] < 0) return flow;
		memset(iter, 0, sizeof(iter));
		ll f;
		while((f = dfs(s, t, INF)) > 0){
			flow += f;
		}
	}
}
int min_cut(int v){
	int count = 1;
	level[v] = 1;
	for(int i = 0; i < G[v].size(); i++){
		edge e = G[v][i];
		if(e.cap > 0 && level[e.to] < 0){ //不走已造訪過的點
			count += min_cut(e.to);
		}
	}
	return count;
}
int main(){
	scanf("%d%d", &n, &m);
	int s = 0, t = n+1;
	ll W = 0;
	for(int i = 1; i <= n; i++){
		ll b;
		cin>>b;
		if(b > 0){ 
			add_edge(s, i, b);
			W += b;
		}
		else if (b < 0) add_edge(i, t, -b);
	}
	for(int i = 0; i < m;i++){
		int a, b;
		cin>>a>>b;
		add_edge(a, b, INF);
	}
	W -= max_flow(s, t);
	memset(level, -1, sizeof(level)); //這裡level 充當visited用
	cout<<min_cut(s)-1<<" "<<W<<endl;
	return 0;
}
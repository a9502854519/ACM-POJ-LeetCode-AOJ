#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define MAX_N 10
#define INF 1000000000
using namespace std;

struct edge{
	int c, to, P, R;
};
struct Node{
	int d, v, s;
	bool operator > (const Node& other)const{
		return d > other.d;
	}
};
priority_queue< Node, vector<Node>, greater<Node> > q;
vector<edge> G[MAX_N];
int dp[MAX_N][1<<MAX_N];
int N, m;
void fill(){
	for(int i = 0; i < MAX_N; i++){
		fill(dp[i], dp[i]+(1<<MAX_N), INF);
	}
}
void out(int s){
	for(int i = N-1; i >= 0; i--){
		printf("%d", ((s>>i)&1) ? 1 : 0);
	}
}
int main(){
	
	scanf("%d%d",&N, &m);
	for(int i = 0; i < m; i++){
		int a, b, c, P, R;
		scanf("%d%d%d%d%d", &a, &b, &c, &P, &R);
		edge e;
		e.c = c-1, e.to = b-1, e.P = P, e.R = R;
		G[a-1].push_back(e);
	}
	fill();
	Node n;
	n.d = 0, n.v = 0, n.s = 1;
	q.push(n);
	dp[0][1] = 0;
	int res = INF;
	while(!q.empty()){
		n = q.top(), q.pop();
		int d = n.d, v = n.v, S = n.s;
		if(dp[v][S] < d) continue;
		if(v == N-1){
			res = d;
			break;
		}
		for(int i = 0; i < G[v].size(); i++){
			edge e = G[v][i];
			int cost = ( (S&(1<<e.c)) ? e.P : e.R), u = e.to;
			if(dp[u][ S|(1<<u) ] > dp[v][S] + cost){
				dp[u][ S|(1<<u) ] = dp[v][S] + cost;
				Node t;
				t.d = dp[u][ S|(1<<u) ], t.v = u, t.s = S|(1<<u);
				q.push(t);
			}
		}
	}
	if(res < INF) cout<<res<<endl;
	else cout<<"impossible\n";
	return 0;
}
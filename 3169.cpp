#include<iostream>
#include<cstdio>
#include<vector>
#define MAX_E 20000+1000
#define MAX_V 1000+1
#define INF 1E9
using namespace std;

struct edge{
	int from, to, cost;
	edge() {}
	edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

int N, ML, MD;
vector<edge> E;
int d[MAX_V];

void add_edge(int from, int to, int cost){
	E.push_back(edge(from, to, cost));
}
void solve(){
	int V = N;
	for(int i = 1; i <= V; i++) d[i] = INF;
	d[1] = 0;
	for(int i = 0; i < V; i++){
		for(int j = 0; j < E.size(); j++){
			edge e = E[j];
			if(d[e.to] > d[e.from] + e.cost){
				d[e.to] = d[e.from] + e.cost;
				if(i == V-1){
					printf("-1\n");
					return;
				}
			}
		}
	}
	printf("%d\n", (d[N] == INF ? -2 : d[N]));
}
int main(){
	scanf("%d%d%d\n", &N, &ML, &MD);
	
	while(ML--){
		int A, B, D;
		scanf("%d%d%d", &A, &B, &D);
		add_edge(A, B, D);
	}
	while(MD--){
		int A, B, D;
		scanf("%d%d%d", &A, &B, &D);
		add_edge(B, A, -D);
	}
	solve();
}
	
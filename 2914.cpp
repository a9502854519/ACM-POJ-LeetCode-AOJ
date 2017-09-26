#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
//#include<ctime>
#define MAX_V 500 
#define INF 1000000000
using namespace std;
//clock_t S, F;

int n, m;
int V;
struct edge{
	int to;
	int cap;
};
int adj[MAX_V][MAX_V];
int par[MAX_V];


void add_edge(int from, int to, int cap){
	//adj matrix
	adj[from][to] += cap;
	adj[to][from] += cap;
}
void init(){
	memset(adj, 0, sizeof(adj));
	V = n;
	for(int i = 0; i < n; i++){
		par[i] = i;
	}
}

void merge(int s, int t){
	//將t併到s
	for(int i = 0; i < n; i++){
		if(i != s && par[i] == i){
			adj[i][s] += adj[i][t];
			adj[s][i] += adj[t][i];
			adj[i][t] = 0, adj[t][i] = 0;
		}
		if(par[i] == t) par[i] = s;
	}
	V--;
}
int MinimumCutPhase(int a){
	int added[n], weight[n];
	int s, size_of_A = 0;
	memset(weight, 0, sizeof(weight));
	memset(added, 0, sizeof(added));
	a = par[a];
	added[a] = 1;
	int to, cap;
	to = a;
	while(++size_of_A < V){
		cap = 0;
		s = to;
		for(int j = 0; j < n; j++){
			int t = par[j];
			if(t == j  && adj[s][t] > 0 && !added[t]){
				weight[t] += adj[s][t];
			}
			if(weight[t] > cap){
				cap = weight[t];
				to = t;
			}
		}
		if(cap > 0){//加入A集合
			added[to] = 1;
			weight[to] = 0;
		}else{
			return 0;
		}
	}
	merge(s, to);
	return cap;
}
int MinimumCut(){
	int res = INF;
	while(V > 1){
		int temp = MinimumCutPhase(0);
		res = min(res, temp);
		if(res == 0) break;
	}
	return res;
}
int main(){
	//clock_t start, finish;
	//start = clock();
	while(scanf("%d%d", &n, &m) != EOF){
		init();
		//S = clock();
		while(m--){
			int a, b; int c;
			scanf(" %d%d%d ",&a, &b, &c);
			add_edge(a, b, c);
		}
		cout<<MinimumCut()<<endl;
		//F = clock();
		//cout<<(double)(F-S)/CLOCKS_PER_SEC<<" sec\n\n";
	}
	//finish = clock();
	//printf("total time : %.4f sec\n", (double)(finish-start)/CLOCKS_PER_SEC);
	return 0;
}
			
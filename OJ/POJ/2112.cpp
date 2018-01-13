#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#define MAX_V 232
#define INF 1000000000
using namespace std;

int K, C, M, V;
int mat[MAX_V][MAX_V];//原始資料
int cap[MAX_V][MAX_V];//鄰接矩陣
int   d[MAX_V][MAX_V];//各點對之間的最短距離
int level[MAX_V];
int iter[MAX_V];

int floyd(){
	int res = 0;
	for(int k = 1; k <= V; k++){
		for(int i = 1; i <= V; i++){
			for(int j = 1; j <= V; j++){
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				res = max(res, d[i][j]);
			}
		}
	}
	return res;
}
void bfs(int s){
	memset(level, -1, sizeof(level));
	queue<int> q;
	level[s] = 0;
	q.push(s);
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int i = 0; i < V; i++){
			if(cap[v][i] > 0 && level[i] < 0){
				level[i] = level[v] + 1;
				q.push(i);
			}
		}
	}
}
int dfs(int v, int t, int f){
	if(v == t)	return f;
	for(int &i = iter[v]; i < V; i++){
		if(cap[v][i] > 0 && level[v] < level[i]){
			int d = dfs(i, t, min(f, cap[v][i]));
			if(d > 0){
				cap[v][i] -= d;
				cap[i][v] += d;
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
bool Check(int x){//x是距離限制
	int s = 0, t = K+C+1;
	memset(cap, 0, sizeof(cap));
	for(int i = K+1; i <= K+C; i++){//從牛
		for(int j = 1; j <= K; j++){//到機器
			if(d[i][j] <= x){//如果牛到機器之間的最短距離...
				cap[i][j] = 1;
			}
			if(i == K+1) cap[j][t] = M;//機器到匯點
		} 
		cap[s][i] = 1; //源點到牛
	}
	return max_flow(s, t) == C;
}
int main(){
	cin>>K>>C>>M;
	V = K+C;
	int ub = 0, lb = 0, mid;
	for(int i = 1; i <= K+C; i++){
		for(int j = 1; j <= K+C; j++){
			scanf("%d", &mat[i][j]);
			d[i][j] = mat[i][j];
			if(i != j && d[i][j] == 0) d[i][j] = INF;
		}
	}
	ub = floyd();
	V += 2;
	while(ub - lb > 1){
		mid = (ub + lb)/2;
		if(Check(mid)) ub = mid;
		else lb = mid;
	}
	cout<<ub<<endl;
	return 0;
}
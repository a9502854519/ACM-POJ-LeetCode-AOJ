#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX_N 1000

using namespace std;

int N, A, B;
vector<int> G[MAX_N];
vector<int> rG[MAX_N];
bool used[MAX_N];
vector<int> vs;
int cmp[MAX_N];
int sx[2], sy[2], x[MAX_N], y[MAX_N];
int sat[MAX_N];

void add_edge(int u, int v){
	G[u].push_back(v);
	rG[v].push_back(u);
}
void dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		if(!used[G[v][i]]) dfs(G[v][i]);
	}
	vs.push_back(v);
}
void rdfs(int v, int k){
	used[v] = true;
	cmp[v] = k;
	for(int i = 0; i < rG[v].size(); i++){
		if(!used[rG[v][i]]) rdfs(rG[v][i], k);
	}
}
int  scc(){
	memset(used, false, sizeof(used));
	for(int i = 0; i < N; i++){
		if(!used[i]) dfs(i);
	}

	memset(used, false, sizeof(used));
	int k = 0;
	for(int i = vs.size() - 1; i >= 0; i--){
		if(!used[vs[i]]) rdfs(vs[i], k++);
	}
	return k;
}
int rev(int v){
	return v >= N ? v - N : v + N;
}
void add_or(int u, int v){
	add_edge(rev(u), v);
	add_edge(rev(v), u);
}
int dis(int i, int j){
	int a = abs(x[i] - sx[sat[i]]) + abs(y[i] - sy[sat[i]]);
	int b = abs(x[j] - sx[sat[j]]) + abs(y[j] - sy[sat[j]]);
	return a + b;
}
int solve(){
	int k = scc();
	for(int i = 0; i < N; i++){
		if(cmp[i] == cmp[i + N]) return -1;
	}
	for(int i = 0; i < N; i++){
		if(cmp[i] > cmp[i + N]){
			sat[i] = 1;
		}else{
			sat[i] = 0;
		}
	}
	int res = 0;
	for(int i = 0; i < N; i++){
		for(int j = i + 1; j < N; j++){
			res = max(res, dis(i, j));
		}
	}
	return res;
}
int main(){
	scanf("%d %d %d\n", &N, &A, &B);
	scanf("%d %d %d %d\n", sx, sy, sx + 1, sy + 1);
	for(int i = 0; i < N; i++){
		scanf("%d %d\n", x + i, y + i);
	}
	while(A--){
		int i, j;
		scanf("%d %d\n", &i, &j);
		add_or(i, j);
		add_or(rev(i), rev(j));
	}
	while(B--){
		int i, j;
		scanf("%d %d\n", &i, &j);
		add_or(rev(i), j);
		add_or(i, rev(j));
	}
	printf("%d\n", solve());
	return 0;
}




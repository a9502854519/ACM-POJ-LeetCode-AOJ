#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_N 1000
#define INF 2147483647
using namespace std;

struct P{
	int u, v;
	P () {}
	P (int u, int v) : u(u), v(v) {}
};
int N, A, B;
vector<int> G[MAX_N];
vector<int> rG[MAX_N];
vector<int> vs;
vector<int> data;
vector<P> friends;
vector<P> hate;
bool used[MAX_N];
int cmp[MAX_N];
int sx[2], sy[2], x[MAX_N], y[MAX_N];
int d[MAX_N][MAX_N];
int tp[MAX_N];

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
int scc(){
	memset(used, false, sizeof(used));
	vs.clear();
	for(int i = 0; i < 2 * N; i++){
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
bool C(int x){
	for(int i = 0; i < 2 * N; i++){
		G[i].clear();
		rG[i].clear();
	}
	for(int i = 0; i < N; i++){
		for(int j = i + 1; j < N; j++){
		//	printf("i = %d j = %d\n", i + 1, j + 1);
			if(d[i][j] > x || d[i][j] < 0){
			//	printf("d = %d  0 0\n", d[i][j]);
				add_or(i, j);
			}
			if(d[i][j + N] > x || d[i][j + N] < 0){
			//	printf("d = %d  0 1\n", d[i][j + N]);
				add_or(i, j + N);
			}
			if(d[i + N][j] > x || d[i + N][j] < 0){
			//	printf("d = %d  1 0\n", d[i + N][j]);
				add_or(i + N, j);
			}
			if(d[i + N][j + N] > x || d[i + N][j + N] < 0){
			//	printf("d = %d  1 1\n", d[i + N][j + N]);
				add_or(i + N, j + N);
			}
			
		//printf("\n");
		}
	}
	scc();
	for(int i = 0; i < N; i++){
		if(cmp[i] == cmp[i + N]) return false;
	}
	return true;
}
int solve(){
	sort(data.begin(), data.end());
	data.erase(unique(data.begin(), data.end()), data.end());
	int ub = data.size(), lb = -1, mid;
	
//	printf("%s\n", C(58468) ? "TRUE" : "FALSE");
	while(ub - lb > 1){
		mid = (ub + lb) / 2;
		if(C(data[mid])) ub = mid;
		else             lb = mid;
	}
	return ub == data.size() ? -1 : data[ub];
}
int main(){
	scanf("%d %d %d\n", &N, &A, &B);
	scanf("%d %d %d %d\n", sx, sy, sx + 1, sy + 1);
	for(int i = 0; i < N; i++){
		scanf("%d %d\n", x + i, y + i);
	}
	for(int i = 0; i < 2 * N; i++){
		for(int j = i + 1; j < 2 * N; j++){
			if(i % N == j % N) d[i][j] = 0;
			else{
				d[i][j] = d[j][i] = abs(x[i % N] - sx[i / N]) + abs(y[i % N] - sy[i / N])
								  + abs(x[j % N] - sx[j / N]) + abs(y[j % N] - sy[j / N])
								  + abs(sx[i / N] - sx[j / N]) + abs(sy[i / N] - sy[j / N]);
				data.push_back(d[i][j]);
			}
		}
	}
	while(A--){
		int i, j;
		scanf("%d %d\n", &i, &j);
		i--; j--;
		//add_or(i, j);
		//add_or(rev(i), rev(j));
		d[i][j] = d[i + N][j + N] = d[j][i] = d[j + N][i + N] = -1;
	}
	while(B--){
		int i, j;
		scanf("%d %d\n", &i, &j);
		i--; j--;
		//add_or(rev(i), j);
		//add_or(i, rev(j));
		d[i][j + N] = d[i + N][j] = d[j][i + N] = d[j + N][i] = -1;
	}
	printf("%d\n", solve());
	return 0;
}




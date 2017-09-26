#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_V 5000

using namespace std;

int R, C, V;

int verti[50][50];
int hori[50][50];
char str[50][60];

int match[MAX_V];
bool used[MAX_V];
vector<int> G[MAX_V];//0~R*C-1為垂直方向，R*C~2*R*C-1是水平方向

void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
bool dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w)){
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}
int bipartite_matching(){
	int res = 0;
	memset(match, -1, sizeof(match));
	for(int v = 0; v < V; v++){
		if(match[v] < 0){
			memset(used, 0, sizeof(used));
			if(dfs(v)){
				res++;
			}
		}
	}
	return res;
}
int main(){
	scanf("%d%d", &R, &C);
	V = R*C*2;
	memset(hori, -1, sizeof(hori));
	for(int i = 0; i < R; i++){
		scanf("%s", str[i]);
		for(int j = 0; j < C; j++){
			if(str[i][j] == '*'){
				if(j == 0 || str[i][j-1] == '.') hori[i][j] = i*C+j + R*C;//點的編號
				else hori[i][j] = hori[i][j-1];
			}
		}
	}
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			if(str[i][j] == '*' && (i == 0 || str[i-1][j] == '.')){
				int u = i*C+j;
				for(int k = i; k < R && str[k][j] == '*'; k++){
					int v = hori[k][j];
					add_edge(u, v);
				}
			}
		}
	}
	printf("%d\n", bipartite_matching());		
	return 0;
}
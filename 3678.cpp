#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX_V 1000 * 2
#define MAX_E 1000000

using namespace std;

int V, E;
vector<int> G[MAX_V];
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];

void add_edge(int u, int v){
	G[u].push_back(v);
	rG[v].push_back(u);
}
void dfs(int v){
	used[v] = true;
	for(int i = 0; i < G[v].size(); i++){
		if(!used[G[v][i]]){
			dfs(G[v][i]);
		}
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
	memset(used, 0, sizeof(used));
	for(int v = 0; v < V; v++){
		if(!used[v]) dfs(v);
	}
	memset(used, 0, sizeof(used));
	int k = 0;
	for(int i = vs.size() - 1; i >= 0; i--){
		if(!used[vs[i]]){
			rdfs(vs[i], k++);
		}
	}
	return k;
}
void solve(){
	V *= 2;
	int k = scc();
	V /= 2;
	/*for(int i = 0; i < 2 * V; i++){
		printf("cmp[%d] = %d\n", i, cmp[i]);
	}*/
	for(int i = 0; i < V; i++){
		if(cmp[i] == cmp[i + V]){
			printf("NO\n");
			return;
		}
	}
	printf("YES\n");
}
int rev(int a){
	if(a >= V) return a - V;
	return a + V;
}
void add_or(int a, int b){
	//!a -> b
	//!b -> a
	add_edge(rev(a), b);
	add_edge(rev(b), a);
}
int main(){
	scanf("%d %d\n", &V, &E);
	for(int i = 0; i < E; i++){
		int a, b, c;
		char ch;
		scanf("%d %d %d %c%*s\n", &a, &b, &c, &ch);
		//a & b = (a | b) & (a | !b) & (!a | b)
		if(ch == 'A'){ //AND
			if(c == 1){
				add_or(a, b);
				add_or(a, b + V);
				add_or(a + V, b);
			}else{
				add_or(a + V, b + V);
			}
		}else if(ch == 'O'){ //OR
			if(c == 1){
				add_or(a, b);
			}else{
				add_or(a + V, b + V);
				add_or(a + V, b);
				add_or(a, b + V);
			}
		}else{ //XOR
			//a ^ b = (a | b) & (!a | !b)
			if(c == 1){
				add_or(a, b);
				add_or(a + V, b + V);
			}else{
				add_or(a + V, b);
				add_or(a, b + V);
			}
		}
	}
	solve();
}
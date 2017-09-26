#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define MAX_V 2000
using namespace std;

int N, M, V;
vector<int> data;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void init(){
	for(int i = 0; i < MAX_V; i++) G[i].clear();
	data.clear();
}

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
bool check(int i, int j){
	int n = i ^ j;
	return (n & (n-1)) == 0 && i != j;
}
void out(int v){
	for(int i = N-1; i >= 0; i--){
		printf("%d",((v>>i)&1) ? 1 : 0);
	}
	cout<<endl;
}
void solve(){
	sort(data.begin(), data.end());
	data.erase(unique(data.begin(), data.end()), data.end());
	V = data.size();
	for(int i = 0; i < V; i++){
		for(int j = i+1; j < V; j++){
			if(check(data[i], data[j])){
				add_edge(i, j);
			}
		}
	}
	printf("%d\n", V - bipartite_matching());
}
int main(){
	char str[15];
	while(cin>>N>>M){
		init();
		if(!N&&!M) break;
		while(M--){
			int a = 0, b = 0;
			scanf("%s",str);
			for(int i = 0; i < N; i++){
				a <<= 1; b <<= 1;
				if(str[i] == '1'){
					a += 1;
				}else if(str[i] == '*'){
					b = 1;
				}	
			}
			data.push_back(a);
			if(b != 0){
				data.push_back(a^b);
			}
		}
		solve();
	}
	return 0;
}
		
	
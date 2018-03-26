#include<iostream>
#include<cstdio>
#include<vector>
#define MAX_N 200

using namespace std;

char mat[MAX_N][MAX_N];
int n, m;
int par[MAX_N]; 
int rank[MAX_N]; 

void init(){
	for(int i = 0; i < n + m; i++){
		rank[i] = 0;
        par[i] = i;
	}
}
int find(int x){
	if(par[x] == x){
		return x; 
	}else{
		return par[x] = find(par[x]);
	}
}
void unite(int x, int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(rank[x] < rank[y]){
		par[x] = y;
	}else{
		par[y] = x;
		if(rank[x] == rank[y]) rank[x]++;
	}
}
bool same(int x, int y){
	return find(x) == find(y);
}


bool solve(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == '#'){
                unite(i, j + n);
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == '.' && same(i, j + n)){
                return false;
            }
        }
    }
    return true;
}
int main(){
    cin >> n >> m;
    init();
    for(int i = 0; i < n; i++){
        scanf("%s", mat[i]);
    }
    printf("%s\n", solve() ? "Yes" : "No");
}
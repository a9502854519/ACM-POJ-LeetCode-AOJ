#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define MAX_N 2000

using namespace std;

int n, m;
int mat[MAX_N][MAX_N];
int st[MAX_N];
int h[MAX_N][MAX_N];
int L[MAX_N], R[MAX_N];
bool check[MAX_N];

int calc(int* height){
	int t = 0;
	for(int i = 0; i < n; i++){

		while(t > 0 && height[ st[t - 1] ] >= height[i]) t--;
		L[i] = t == 0 ? 0 : st[t - 1] + 1;
		st[t++] = i;
	}
	
	t = 0;
	for(int i = n - 1; i >= 0; i--){
		while(t > 0 && height[ st[t - 1] ] >= height[i]) t--;
		R[i] = t == 0 ? n : st[t - 1];
		st[t++] = i;
	}
	int res = 0;
	for(int i = 0; i < n; i++){
		res = max(res, (R[i] - L[i]) * height[i]);
	}
	return res;
}
void solve(){
	int res = 0;
	for(int i = m - 1; i >= 0; i--){
		if(check[i]){
			res = max(res, calc(h[i]));
		}
	}
	printf("%d\n", res);
}
int main(){
	while(cin>>m>>n && (n || m)){
		memset(h, 0, sizeof(h));
		memset(check, 0, sizeof(check));

		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
			        scanf("%d", &mat[i][j]);				
			        if(mat[i][j] == 1) h[i][j] = i == 0 ? 1 : h[i-1][j] + 1;
			        if(i > 0 && mat[i][j] == 0 && mat[i-1][j] == 1) check[i-1] = true;
			        else if(mat[i][j] == 1 && i == m - 1) check[i] = true;
	
			}	
		}
		solve();
	}
	return 0;
}

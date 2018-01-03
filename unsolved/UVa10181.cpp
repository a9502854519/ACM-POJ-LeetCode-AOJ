#include<iostream>
#include<queue>
#include<cstdio>
#include<cmath>
#include<utility>
#define MAX_STEP 50
#define INF 1E9

using namespace std;


int puzzle[4][4];
const int n = 4;
int dx[] = {0,  0, 1, -1};
int dy[] = {1, -1, 0,  0};
char dir[] = {'R', 'L', 'D', 'U'};
int ct = 0;
int limit;

void swap(int &a, int &b){
	a ^= b;
	b ^= a;
	a ^= b;
}
void show_route(){
	
}
int hstar(){
	int res = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(puzzle[i][j] != 0){
				res += abs((puzzle[i][j] - 1) / n - i) + abs((puzzle[i][j] - 1) % n - j);
			}
		}
	}
	return res;
}
bool solvable(){
	
}
bool check(){
	
}
int dfs(int num, int direction, int x, int y){
	
}
void solve(){
	
}
int main(){
	int T;
	cin >> T;
	while(T--){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%d", &puzzle[i][j]);
			}
		}
		solve();
		cout << "ct = " << ct << endl;
	}
	return 0;
}
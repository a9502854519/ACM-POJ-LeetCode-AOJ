#include<iostream>
#include<queue>
#include<cstdio>
#include<cmath>
#include<utility>
#define MAX_STEP 45
#define INF 1E9

using namespace std;


int puzzle[4][4];
const int n = 4;
int dx[] = {0,  0, 1, -1};
int dy[] = {1, -1, 0,  0};
char dir[] = {'R', 'L', 'D', 'U'};
int forbidden[] = {1, 0, 3, 2};
int ct = 0;
int limit;
vector<char> re;

void swap(int &a, int &b){
	a ^= b;
	b ^= a;
	a ^= b;
}
void show_route(){
	for(int i = 0; i < re.size(); i++){
		cout << re[i];
	}
	cout << endl;
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
	int res = 0, t = 0;
	for(int i = 0; i < n * n; i++){
		int x = i / n, y = i % n;
		for(int j = i + 1; j < n * n; j++){
			int nx = j / n, ny = j % n;
			if(puzzle[x][y] > puzzle[nx][ny]) res = 1 - res;
		}

		if(puzzle[x][y] == 0) t = (3 - x + 3 - y) & 1;
	}
	return (res + t) & 1;
}
bool check(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == 3 && j == 3) break;
			if(puzzle[i][j] - 1 != i * n + j){
				return false;
			}
		}
	}	
	return true;
}
int dfs(int num, int direction, int x, int y){
	if(x == 3 && y == 3 && check()){
		return num;
	}
	if(num + hstar() >= limit) return INF;
	ct++;
	for(int i = 0; i < 4; i++){
		if(forbidden[i] == direction) continue;

		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

		swap(puzzle[nx][ny], puzzle[x][y]);
		re.push_back(dir[i]);

		if(dfs(num + 1, i, nx, ny) < INF) return num;

		swap(puzzle[nx][ny], puzzle[x][y]);
		re.pop_back();
	}
	return INF;
}
void solve(){
	int x, y;
	ct = 0;
	if(solvable()){
		re.clear();
		for(int i = 0; i < n * n; i++){
			if(puzzle[i / n][i % n] == 0){
				x = i / n, y = i % n;
				break;
			}
		}
		for(limit = hstar(); limit <= MAX_STEP; limit++){
			cout << limit << endl;
			if(dfs(0, -1, x, y) < INF){
				show_route();
				return;
			}
		}
	}
	printf("This puzzle is unsolvable.\n");
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

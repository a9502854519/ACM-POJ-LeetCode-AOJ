#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define MAX_N 50

using namespace std;

int n, m;
int start_x, start_y;
char maze[MAX_N][MAX_N];
string s;

int x[] = { 0, 0, -1, 1};
int y[] = {-1, 1,  0, 0};

int solve(){
	int per[] = {0, 1, 2, 3};
	int res = 0;
	do{
		int i = start_x, j = start_y;
		for(int k = 0; k < s.size(); k++){
			i += x[per[s[k] - '0']];
			j += y[per[s[k] - '0']];
			if(i < 0 || i >= n || j < 0 || j >= m || maze[i][j] == '#') break;
			else if(maze[i][j] == 'E'){
				res++;
				break;
			}
		}
	}while(next_permutation(per, per + 4));
	return res;
}
int main(){
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> maze[i][j];
			if(maze[i][j] == 'S'){
				start_x = i, start_y = j;
			}
		}
	}
	cin >> s;
	cout << solve() << endl;
	return 0;
}


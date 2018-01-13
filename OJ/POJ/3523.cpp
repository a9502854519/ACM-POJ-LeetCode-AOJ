#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<unordered_map>
#include<vector>
#include<utility>
#include<map>
#define MAX_W 16 + 5
#define MAX_N 3 + 2
#define INF 0x3f3f3f3f

using namespace std;
typedef pair<int, int> P;

int w, h, n;
char m[MAX_W][MAX_W];
int d[MAX_N][MAX_W][MAX_W];
int dir[MAX_N];
map<int, int>::iterator it;
int x[] = {0, 1, -1, 0,  0}; //不動/下/上/右/左
int y[] = {0, 0,  0, 1, -1};
int ct = 0;

int hstar(int cur){
	int res = 0;
	for(int i = 0; i < n; i++){
		int sx = (cur >> 4) & 0xf;
		int sy =  cur & 0xf;
		cur >>= 8;
		res = max(res, d[i][sx][sy]);
	}
	return res;
}
int check(int cur, int *dir){
	int sxy[3], nxy[3], nxt = 0;
	for(int i = 0; i < 3; i++){
		sxy[i] = (cur >> (i * 8)) & 0xff;
		int nx = ((sxy[i] >> 4) & 0xf) + x[dir[i]];
		int ny = (sxy[i] & 0xf) + y[dir[i]];
		nxy[i] = (nx << 4) | ny;
	}
	for(int i = 0; i < n; i++){
		int nx = (nxy[i] >> 4) & 0xf;
		int ny = nxy[i] & 0xf;
		if(m[nx][ny] == '#') return 0; //hit the wall
		for(int j = i + 1; j < n; j++){
			if((nxy[i] == nxy[j]) || (nxy[i] == sxy[j] && sxy[i] == nxy[j])) return 0; // overlap && switch
		}
		nxt |= (nxy[i] << (i * 8));
	}
	return nxt;
}
// void show(int cur){
	// for(int i = 0; i < n; i++){
		// int sx = cur >> 4 & 0xf;
		// int sy = cur & 0xf;
		// cur >>= 8;
		// printf("%c : (%d, %d)\n", i + 'a', sx, sy);
	// }
// }
int solve(){
	memset(d, 0x3f, sizeof(d));
	//BFS
	for(int i = 0; i < n; i++){
		int sx, sy;
		for(int j = 0; j < w * h; j++){
			if(m[j / w][j % w] == i + 'A'){
				sx = j / w, sy = j % w;
				break;
			}
		}
		queue<P> que;
		que.push(make_pair(sx, sy));
		d[i][sx][sy] = 0;
		while(!que.empty()){
			P p = que.front(); que.pop();
			for(int j = 1; j < 5; j++){
				int nx = p.first + x[j];
				int ny = p.second + y[j];
				if(m[nx][ny] != '#' && d[i][nx][ny] > d[i][p.first][p.second] + 1){
					d[i][nx][ny] = d[i][p.first][p.second] + 1;
					que.push(make_pair(nx, ny));
				}
			}
		}
	}
	int cur = 0, end = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < w * h; j++){
			if(m[j / w][j % w] == i + 'a'){
				cur |= ((j / w) << (8 * i + 4));
				cur |= ((j % w) << (8 * i));
			}
			if(m[j / w][j % w] == i + 'A'){
				end |= ((j / w) << (8 * i + 4));
				end |= ((j % w) << (8 * i));
			}
		}
	}
	priority_queue<P, vector<P>, greater<P> > que;
	unordered_map<int, int> mp;
	mp[cur] = 0;
	que.push(make_pair(hstar(cur), cur));
	while(!que.empty()){
		cur = que.top().second; que.pop();
		
		if(cur == end) return mp[cur];
		
		ct++;
		
		for(int i = 0; i < 5; i++){
		    dir[0] = i;
			for(int j = 0; j < (n < 2 ? 1 : 5); j++){
				dir[1] = j;
				for(int k = 0; k < (n < 3 ? 1 : 5); k++){
					dir[2] = k;
					int nx = check(cur, dir);
					
					if(nx > 0){ //確認下一步是合法的
						if(mp.find(nx) == mp.end() || mp[nx] > mp[cur] + 1){
							mp[nx] = mp[cur] + 1;
							que.push(make_pair(mp[nx] + hstar(nx), nx)); //d(v) + h*(v)
						}
					}
					
				}
			}
		}
	}
	return -1;
}
int main(){
	while(scanf("%d %d %d\n", &w, &h, &n) != EOF && (w || h || n)){
		for(int i = 0; i < h; i++){
			scanf("%[^\n]%*c", m[i]);
		}
		ct = 0;
		cout << solve() << endl;
		printf("ct = %d\n", ct);
	}
	
	return 0;
}
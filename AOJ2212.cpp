#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#define max_p 10
#define MAX_N 50
#define MAX_STATE 120
#define INF 0x3f3f3f3f

using namespace std;

struct S{
	int x, y, k;
	S() {}
	S(int x, int y, int k) : x(x), y(y), k(k) {}
};
char mat[MAX_N][MAX_N];
vector<string> P;
int N, M;
int start_x, start_y, end_x, end_y;
int dp[MAX_N][MAX_N][MAX_STATE];
int next[MAX_STATE][4];
bool ng[MAX_STATE];

int h[] = {0, 0, -1, 1};
int v[] = {-1, 1, 0, 0};
char UDLR[] = "UDLR";

int solve(){
	vector<string> pfx;
	for(int i = 0; i < P.size(); i++){
		for(int j = 0; j <= P[i].length(); j++){
			pfx.push_back(P[i].substr(0, j));
		}
	}
	sort(pfx.begin(), pfx.end());
	pfx.erase(unique(pfx.begin(), pfx.end()), pfx.end());
	

	for(int i = 0; i < pfx.size(); i++){
		for(int j = 0; j < P.size(); j++){
			if(P[j].length() <= pfx[i].length() &&
					pfx[i].substr(pfx[i].length() - P[j].length(), P[j].length()) == P[j]){
				ng[i] = true;
				break;
			}
		}
		for(int j = 0; j < 4; j++){
			if(!ng[i]){
				string s = pfx[i] + UDLR[j];
				int k;
				for(;;){
					k = lower_bound(pfx.begin(), pfx.end(), s) - pfx.begin();
					if(k < pfx.size() && pfx[k] == s){
						next[i][j] = k;
						break;
					}
					s = s.substr(1);
				}
			}
		}
	}

	memset(dp, 0x3f, sizeof(dp));
	dp[start_x][start_y][0] = 0;
	queue<S> que;
	que.push(S(start_x, start_y, 0));

	while(!que.empty()){
		int cx = que.front().x, cy = que.front().y, ck = que.front().k;
		que.pop();

		if(cx == end_x && cy == end_y) return dp[cx][cy][ck];

		for(int i = 0; i < 4; i++){
			int nx = cx + v[i], ny = cy + h[i], nk = next[ck][i];
			if(!ng[nk]){
				if(0 <= nx && nx < N && 0 <= ny && ny < M && mat[nx][ny] != '#'){
					if(dp[nx][ny][nk] > dp[cx][cy][ck] + 1){
						dp[nx][ny][nk] = dp[cx][cy][ck] + 1;
						que.push(S(nx, ny, nk));
					}
				}
			}
		}
	}
	return -1;
}
void init(){
	P.clear();
	memset(ng, false, sizeof(ng));
	memset(next, 0, sizeof(next));
}
int main(){
	while(scanf("%d %d\n", &N, &M) && (N || M)){
		init();
		for(int i = 0; i < N; i++){
			scanf("%s", mat[i]);
			for(int j = 0; j < M; j++){
				if(mat[i][j] == 'S'){
					start_x = i;
					start_y = j;
				}
				else if(mat[i][j] == 'G'){
					end_x = i;
					end_y = j;
				}
			}
		}
		int tmp;
		cin>>tmp;
		for(int i = 0; i < tmp; i++){
			string s;
			cin>>s;
			P.push_back(s);
		}
		printf("%d\n", solve());
	}
	return 0;
}

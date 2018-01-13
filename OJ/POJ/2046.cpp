#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
#define INF 0x3f3f3f3f

using namespace std;
typedef unsigned long long ull;


int m[4][8];
int R = 4, C = 8;
ull B = 10000007;
ull G = 3426396420656039308;
map<int, int> h;     //距離目標狀態的距離

void init(){
	memset(m, 0, sizeof(m));
	h.clear();
	h[G] = 0;
	for(int i = 0; i < R; i++) m[i][0] = 11 + i * 10;
}
ull calc_hash(){
	ull t = 0;
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			t = t * B + m[i][j];
		}
	}
	return t;
}
void swap(int &a, int &b){
	a ^= b;
	b ^= a;
	a ^= b;
}
int solve(){//回傳與目標狀態的距離
	ull t = calc_hash();
	if(h.find(t) != h.end()){ //代表曾造訪過這個節點
		return h[t];
	}
	/***
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			printf("%2d ", m[i][j]);
		}
		printf("\n");
	}
	cout << endl;
	/***/
	//既不是目標狀態，也沒造訪過
	int p[48];
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			p[m[i][j]] = i * C + j;
		}
	}
	int d = INF;
	for(int i = 0; i < R; i++){
		for(int j = 1; j < C; j++){
			if(m[i][j] == 0 && m[i][j - 1] % 10 < 7 && m[i][j - 1] > 0){
				int x = p[m[i][j - 1] + 1] / C;
				int y = p[m[i][j - 1] + 1] % C;
				swap(m[i][j], m[x][y]);
				d = min(d, solve() + 1);		
				swap(m[i][j], m[x][y]);
			}
		}
	}
	h[t] = d;
	return d;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		init();
		for(int i = 0; i < R; i++){
			for(int j = 1; j < C; j++){
				scanf("%d", &m[i][j]);
				if(m[i][j] % 10 == 1) m[i][j] = 0;
			}
		}
		int res = solve();
		printf("%d\n", res == INF ? -1 : res);
	}	
}

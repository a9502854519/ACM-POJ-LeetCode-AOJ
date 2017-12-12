#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_N (1<<16)
#define MAX_M (1<<16)
#define MAX_DAT_SIZE (1<<19)-1
#define INF ((1<<31) - 1)

using namespace std;

struct P{
	int x1, y1, x2, y2, id;
	P () {}
	P(int x1, int y1, int id) : x1(x1), y1(y1), id(id) {}
	P(int x1, int y1, int x2, int y2, int id) : x1(x1), y1(y1), x2(x2), y2(y2), id(id) {}
};

int N, M;
int dat_size;
vector<int> xs, ys;
vector<P> WB_x, WB_y;
int dat[MAX_DAT_SIZE];
int dis[MAX_M], hit[MAX_M], ct[MAX_N];

void compress(){
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
}
int get_x(int x){
	return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}
int get_y(int y){
	return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}
bool cmp_x(const P& a, const P& b){
	return a.x1 < b.x1 || (a.x1 == b.x1 && a.y1 < b.y1);
}
bool cmp_y(const P& a, const P& b){
	return a.y1 < b.y1 || (a.y1 == b.y1 && a.x1 < b.x1);
}
void init(int n_){
	dat_size = 1;
	while(dat_size < n_) dat_size *= 2;
}
void update(int a, int b, int k, int l, int r, int v){
	if(b <= l || a >= r) return;
	if(a <= l && b >= r){//totally overlap
		dat[k] = v;
		return;
	}
	int lch = 2 * k + 1, rch = 2 * k + 2;
	if(dat[k] != -1){
		dat[lch] = dat[rch] = dat[k];
	}
	update(a, b, lch, l, (l + r) / 2, v);
	update(a, b, rch, (l + r) / 2, r, v);
	if(dat[lch] == dat[rch]){
		dat[k] = dat[lch];
	}else{
		dat[k] = -1;
	}
}
int query(int a, int b, int k, int l, int r){
	if(a >= r || b <= l) return -1;
	if(dat[k] != -1 || (a <= l && b >= r)) return dat[k];
	
	int v1 = query(a, b, 2 * k + 1, l, (l + r) / 2);
	if(v1 != -1) return v1;
	return query(a, b, 2 * k + 2, (l + r) / 2, r);
}
int query(int a, int b){
	return query(a, b, 0, 0, dat_size);
}
void update(int a, int b, int v){//[a, b)
	update(a, b, 0, 0, dat_size, v);
}
void fly_x(int i, int c){
	for(; i < WB_x.size() && i >= 0; i += c){
		int id = WB_x[i].id;
		if(id < N){ //wall
			int y1 = get_y(WB_x[i].y1),
			    y2 = get_y(WB_x[i].y2);
			update(y1, y2+1, i);
		}else{
			id -= N;
			int x = WB_x[i].x1, y = get_y(WB_x[i].y1);
			int wall_id = query(y, y+1);
			
			if(wall_id >= 0 && dis[id] > abs(x - WB_x[wall_id].x1)){
				dis[id] = abs(x - WB_x[wall_id].x1);
				hit[id] = WB_x[wall_id].id;
			}
		}
	}
}
void fly_y(int i, int c){
	for(; i < WB_y.size() && i >= 0; i += c){
		int id = WB_y[i].id;
		if(id < N){ //wall
			int x1 = get_x(WB_y[i].x1), 
			    x2 = get_x(WB_y[i].x2);
			update(x1, x2 + 1, i);
		}else{
			id -= N;
			int x = get_x(WB_y[i].x1), y = WB_y[i].y1;
			int wall_id = query(x, x+1);
			if(wall_id >= 0 && dis[id] > abs(y - WB_y[wall_id].y1)){
				dis[id] = abs(y - WB_y[wall_id].y1);
				hit[id] = WB_y[wall_id].id;
			} 
		}
	}
}
void solve(){
	compress();
	fill(dis, dis + M, INF);
	//往左飛
	sort(WB_x.begin(), WB_x.end(), cmp_x);
	init(ys.size());
	memset(dat, -1, sizeof(dat));
	fly_x(0, 1);
	//往右飛
	memset(dat, -1, sizeof(dat));
	fly_x(WB_x.size() - 1, -1);
	
	//往下飛
	sort(WB_y.begin(), WB_y.end(), cmp_y);
	init(xs.size());
	memset(dat, -1, sizeof(dat));
	fly_y(0, 1);
	//往上飛
	memset(dat, -1, sizeof(dat));
	fly_y(WB_y.size() - 1, -1);
	
	
	memset(ct, 0, sizeof(ct));
	for(int i = 0; i < M; i++) ct[hit[i]]++;
	for(int i = 0; i < N; i++) printf("%d\n", ct[i]);
}
void swap(int& a, int& b){
	a ^= b;
	b ^= a;
	a ^= b;
}
int main(){
	scanf("%d %d", &N, &M);
	for(int i = 0; i < N; i++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
		
		if(x1 == x2 && y1 > y2) swap(y1, y2);
		else if(y1 == y2 && x1 > x2) swap(x1, x2);
		
		if(x1 == x2){
			WB_x.push_back(P(x1, y1, x2, y2, i));
			WB_y.push_back(P(x1, y1, x1, y1, i));
			WB_y.push_back(P(x2, y2, x2, y2, i));
		}else{
			WB_x.push_back(P(x1, y1, x1, y1, i));
			WB_x.push_back(P(x2, y2, x2, y2, i));
			WB_y.push_back(P(x1, y1, x2, y2, i));
		}
		xs.push_back(x1); xs.push_back(x2);
		ys.push_back(y1); ys.push_back(y2);
	}
	for(int i = 0; i < M; i++){
		int x, y;
		scanf("%d %d\n", &x, &y);
		
		WB_x.push_back(P(x, y, i + N));
		WB_y.push_back(P(x, y, i + N));
		xs.push_back(x);
		ys.push_back(y);
	}
	solve();
	return 0;
}

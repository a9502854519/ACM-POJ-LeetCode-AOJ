#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_N 50000
#define MAX_M 50000
#define MAX_DAT_SIZE 65536
#define INF 1E9

using namespace std;

int N, M, dat_x_size, dat_y_size;

vector<int> xs, ys;
vector<int> dat_x[MAX_DAT_SIZE];//橫向的線段樹
vector<int> dat_y[MAX_DAT_SIZE];//垂直的線段樹

struct Bird{
	int x, y, hit, distance;
	Bird() {distance = INF;}
	Bird(int x, int y) : x(x), y(y) {}
}bird[MAX_M];

struct Line{
	int x1, y1, x2, y2;
	Line() {}
	Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
}line[MAX_N];

void compress(){
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
}
void init(){
	dat_x_size = 1;
	while(dat_x_size < xs.size()) dat_x_size *= 2;
	
	dat_y_size = 1;
	while(dat_y_size < ys.size()) dat_y_size *= 2;
}
void update(vector<int> dat[], int n, int x, int num){
	int k = x + n - 1;
	dat[k].push_back(num);
	while(k > 0){
		k = (k - 1) / 2;
		dat[k].push_back(num);
	}
}
vector<int> query(vector<int> dat[], int a, int b, int k, int l, int r){
	vector<int> res;
	if(a >= r || b <= l){
		res.resize(0);
		return res;
	}
	else if(a <= l && b >= r){
		return dat[k];
	}
	
	vector<int> v1 = query(dat, a, b, 2 * k + 1, l, (l + r) / 2);
	vector<int> v2 = query(dat, a, b, 2 * k + 2, (l + r) / 2, r);
	res.resize(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), res.begin());
	return res;
}
vector<int> query(vector<int> dat[], int n, int a, int b){
	return query(dat, a, b, 0, 0, n);
}
void solve(){
	compress();//座標壓縮
	init();
	printf("M = %d\n", M); 
	for(int i = 0; i < M; i++){
		int x = lower_bound(xs.begin(), xs.end(), bird[i].x) - xs.begin();
		int y = lower_bound(ys.begin(), ys.end(), bird[i].y) - ys.begin();
		printf("i = %d  y = %d\n", i, y);
		update(dat_x, dat_x_size, x, i);
		update(dat_y, dat_y_size, y, i);
	}
	//printf("MAX_X = %d  MAX_Y = %d\n", xs.size(), ys.size());
	/*for(int i = 0; i < xs.size(); i++){
		printf("%d ", xs[i]);
	}
	printf("\n");*/
	/*for(int i = 0; i < ys.size(); i++){
		printf("%d ", ys[i]);
	}
	printf("\n");*/
	
}
int main(){
	scanf("%d %d", &N, &M);
	
	for(int i = 0; i < N; i++){
		scanf("%d %d %d %d\n", &line[i].x1, &line[i].y1, &line[i].x2, &line[i].y2);
		xs.push_back(line[i].x1); xs.push_back(line[i].x2);
		ys.push_back(line[i].y1); ys.push_back(line[i].y2);
	}
	for(int i = 0; i < M; i++){
		scanf("%d %d\n", &bird[i].x, &bird[i].y);
		xs.push_back(bird[i].x);
		ys.push_back(bird[i].y);
	}
	solve();
}
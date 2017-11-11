#include<iostream>
#include<cstring>
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
int bird_x[MAX_M], bird_y[MAX_M], hit[MAX_M], dis[MAX_M];
int line_x1[MAX_N], line_y1[MAX_N], line_x2[MAX_N], line_y2[MAX_N];
int ct[MAX_N];

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
void check(vector<int> dat[], int n, int x1, int x2, int y1, int y2, int* bird, int line_num){
	vector<int> res = query(dat, n, x1, x2);
	for(int i = 0; i < res.size(); i++){
		int k = res[i];
		if(dis[k] > abs(y1 - bird[k])){
			dis[k] = abs(y1 - bird[k]);
			hit[k] = line_num;
		}
		if(dis[k] > abs(y2 - bird[k])){
			dis[k] = abs(y2 - bird[k]);
			hit[k] = line_num;
		}
	}
}
void solve(){
	fill(dis, dis + M, INF);
	compress();//座標壓縮
	init();
	for(int i = 0; i < M; i++){
		int x = lower_bound(xs.begin(), xs.end(), bird_x[i]) - xs.begin();
		int y = lower_bound(ys.begin(), ys.end(), bird_y[i]) - ys.begin();
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
	for(int i = 0; i < N; i++){
		int x1 = lower_bound(xs.begin(), xs.end(), line_x1[i]) - xs.begin(),
		    x2 = lower_bound(xs.begin(), xs.end(), line_x2[i]) - xs.begin();
		int y1 = line_y1[i], y2 = line_y2[i];
		check(dat_x, dat_x_size, min(x1, x2), max(x1, x2) + 1, y1, y2, bird_y, i);

		x1 = line_x1[i], x2 = line_x2[i];
		y1 = lower_bound(ys.begin(), ys.end(), line_y1[i]) - ys.begin();
		y2 = lower_bound(ys.begin(), ys.end(), line_y2[i]) - ys.begin();
		check(dat_y, dat_y_size, min(y1, y2), max(y1, y2) + 1, x1, x2, bird_x, i);
	}
	memset(ct, 0, sizeof(ct));
	for(int i = 0; i < M; i++) ct[hit[i]]++;
	for(int i = 0; i < N; i++) printf("%d\n", ct[i]);
}
int main(){
	scanf("%d %d", &N, &M);
	
	for(int i = 0; i < N; i++){
		scanf("%d %d %d %d\n", line_x1 + i, line_y1 + i, line_x2 + i, line_y2 + i); 
		xs.push_back(line_x1[i]); xs.push_back(line_x2[i]);
		ys.push_back(line_y1[i]); ys.push_back(line_y2[i]);
	}
	for(int i = 0; i < M; i++){
		scanf("%d %d\n", bird_x + i, bird_y + i);
		xs.push_back(bird_x[i]);
		ys.push_back(bird_y[i]);
	}
	solve();
}

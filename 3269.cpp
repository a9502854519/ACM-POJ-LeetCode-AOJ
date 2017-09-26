#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_N 100000
using namespace std;

int n;

struct p{
	int x, y, id;
	p() {}
	p(int x, int y, int id) : x(x), y(y), id(id) {}
};
vector<p> Point;
vector<int> G[MAX_N];
void add_edge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}
bool sort_y(const p& a, const p& b){
	return a.y < b.y || (a.y == b.y && a.x < b.x);
}
bool sort_x(const p& a, const p& b){
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
bool sort_id(const p&a, const p& b){
	return a.id < b.id;
}
bool intersec_check(int a1, int a2, int b1, int b2){
	if((Point[a1].x - Point[b1].x)*(Point[a2].x - Point[b2].x) < 0 && 
	   (Point[a1].y - Point[b1].y)*(Point[a2].y - Point[b2].y) < 0) return true;
	return false;
}
	
int solve(){
	int res = 0;
	sort(Point.begin(), Point.end(), sort_y);
	for(int i = 0; i < n; i += 2){
		if(Point[i].y != Point[i+1].y) return -1;
		res += Point[i+1].x - Point[i].x;
		add_edge(Point[i+1].id, Point[i].id);
	}
	sort(Point.begin(), Point.end(), sort_x);
	for(int i = 0; i < n; i += 2){
		if(Point[i].x != Point[i+1].x) return -1;
		res += Point[i+1].y - Point[i].y;
		add_edge(Point[i+1].id, Point[i].id);
	}
	sort(Point.begin(), Point.end(), sort_id);
	for(int v = 0; v < n; v++){
		int a1 = G[v][0], b1 = G[v][1];
		int a2, b2;
		//printf("a1 = (%d, %d), b1 = (%d, %d)\n", Point[a1].x, Point[a1].y, Point[b1].x, Point[b1].y);
		for(int i = 0; i < 2; i++) if(G[a1][i] != v) a2 = G[a1][i];
		for(int i = 0; i < 2; i++) if(G[b1][i] != v) b2 = G[b1][i];
		//printf("a2 = (%d, %d), b2 = (%d, %d)\n", Point[a2].x, Point[a2].y, Point[b2].x, Point[b2].y);
		if((a2 == b2 && n > 4) || intersec_check(a1, a2, b1, b2)) return -1;
	}
	return res;
}

void init(){
	Point.clear();
	for(int i = 0; i < n; i++) G[i].clear();
}
int main(){
	int c;
	cin>>c;
	while(c--){
		cin>>n;
		init();
		for(int i = 0; i < n; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			Point.push_back(p(x, y, i));
		}
		printf("%d\n", solve());
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<deque>
//#include<ctime>
#define EPS 1E-12
#define INF 1E10
#define MAX_n 100000
using namespace std;

int n, m;
double add(double a, double b){
	if(abs(a+b) < EPS*(abs(a) + abs(b))) return 0;
	return a+b;
}
struct P{
	double x, y;
	P () {}
	P(double x, double y) : x(x), y(y) {}
	P operator + (P p){
		return P(add(x, p.x), add(y, p.y));
	}
	P operator - (P p){
		return P(add(x, -p.x), add(y, -p.y));
	}
	P operator * (double d){
		return P(x*d, y*d);
	}
	double dot(P p){
		return add(x*p.x, y*p.y);
	}
	double det(P p){
		return add(x*p.y, -y*p.x);
	}
};

struct L{
	double a, b, c;
	P v;
	L() {}
	L(double a, double b, double c) : a(a), b(b), c(c) {
		v = P(b, -a);
	}
	P cross(L line){// 求交點
		double delta, deltax, deltay;
		delta  = a*line.b - b*line.a;
		deltax = c*line.b - b*line.c;
		deltay = a*line.c - c*line.a;
		return P(deltax/delta, deltay/delta);
	}
	bool check(P p){
		//return v.det((p-P(0, c/b))) >= 0;
		return add(a*p.x, b*p.y) > c - EPS;
	}
}Lines[MAX_n];

bool cmp(const L& a, const L& b){
	P v = a.v; int t = v.det(b.v);
	if(t != 0) return t > 0;
	return (a.c/a.b) > (b.c/b.b)+EPS;
}
void solve(){
	sort(Lines, Lines+n, cmp);
	int cm = 1;
	for(int i = 1; i < n; i++){
		if(Lines[i].v.x*Lines[cm-1].v.y != Lines[i].v.y*Lines[cm-1].v.x) {
			Lines[cm++] = Lines[i];
		}
	}
	n = cm;
	deque<L> que;
	/**壓入前兩條線**/
	que.push_back(Lines[0]);
	if(n > 1) que.push_back(Lines[1]);
	
	/**計算半平面交集**/
	for(int i = 2; i < n; i++){
		while(que.size() > 1){
			int t = que.size();
			P p = que[t-1].cross(que[t-2]);
			if(!Lines[i].check(p)) que.pop_back();
			else break;
		}
		while(que.size() > 1){
			P p = que[0].cross(que[1]);
			if(!Lines[i].check(p)) que.pop_front();
			else break;
		}
		que.push_back(Lines[i]);
	}
	while(que.size() > 1){
		int t = que.size();
		P p = que[t-1].cross(que[t-2]);
		if(!que.front().check(p)) que.pop_back();
		else break;
	}
	
	while(m--){
		double S, T;
		scanf("%lf %lf", &S, &T);
		P v = P(T, -S);
		int lb = -1, ub = que.size(), mid;
		while(ub - lb > 1){
			mid = (ub+lb)/2;
			if(v.x*que[mid].v.y-v.y*que[mid].v.x >= 0) ub = mid;
			else lb = mid;
		}
		//若兩條線重合...
		if(ub < que.size() && v.x*que[ub].v.y == v.y*que[ub].v.x){
			/*bool good = true;
			if(ub > 0){//last line....
				P p = que[ub].cross(que[ub-1]);
				if(p.y < 0-EPS) good = false;
			}
			if(ub < que.size() - 1){//next line...
				P p = que[ub].cross(que[ub+1]);
				if(p.x < 0-EPS) good = false;
			}
			if(good) 
			else printf("IMPOSSIBLE\n");*/
			printf("%.5f\n", que[ub].c*v.x/que[ub].v.x);
		}else{
			if(ub == 0 || ub == que.size()){
				printf("IMPOSSIBLE\n");
			}else{
				P p = que[ub].cross(que[ub-1]);
				printf("%.5f\n", S*p.x+T*p.y);
			}
		}
	}
}
int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++){
		double a, b, c;
		scanf("%lf %lf %lf", &a, &b, &c);
		Lines[i] = L(a, b, c);
	}
	solve();
	return 0;
}

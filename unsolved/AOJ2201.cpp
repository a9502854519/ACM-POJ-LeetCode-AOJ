#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define EPS 1E-10
#define sqr(x) x*x

using namespace std;

#define pi acos(-1);
int N;
struct Line{
	double a, b, c;
	Line() {}
	Line(double a, double b, double c) : a(a), b(b), c(c) {}
};
struct point{
	double x, double y;
	point() {}
	point(double x, double y) : x(x), y(y) {}
}
struct R{
	double x, y, r, m, id;
	R(){}
	R(double x, double y, double r, double m, double id) : x(x), y(y), r(r), m(m), id(id) {}
	bool operator < (const R& other){
		return r < other.r;
	}
	bool isParallel(R other){
		return abs(other.r - r) < EPS;
	}
	point intersection_point(R other){
		
	vector<Line> Outer_common_tangent(R other){
		double theta1;
		if(abs(other.x-x) < EPS) theta1 = pi;
		else theta1 = atan((other.y-y)/(other.x-x));
		if(!isParallel(other)){//外公切線不平行
			double theta2 = asin((other.r-r)/(sqrt(sqr(other.x-x)*sqr(other.y-y))));
			//求兩條線的交點
			
			
			
	vector<Line> Common_tangent(R other){
		vector<Line> lines;
	}
		
};

vector<R> data;
void init(){
	data.clear();
}

void solve(){
	sort(data.begin(), data.end());
	printf("%d\n", N == 1 ? 1 : res);
}
int main(){
	while(cin>>N){
		if(!N) break;
		init();
		for(int i = 0; i < N; i++){
			int x, y, r, m;
			scanf("%d%d%d%d", &x, &y, &r, &m);
			data.push_back(R(x, y, r+m, 0, i));
			data.push_back(R(x, y, r, m, i));
		}
		solve();
	}
	return 0;
}
		
	
	
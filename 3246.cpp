#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
#define EPS 1E-10
#define INF 1E99

using namespace std;

int n, half_point;
double add(double a, double b){
	if(abs(a+b) < EPS*(abs(a) + abs(b))) return 0;
	return a+b;
}
struct P{
	double x, y;
	int id;
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
	bool operator < (const P& other) const{
		if(x != other.x) return x < other.x;
		return y < other.y;
	}
};
double dist(P p, P q){
	return sqrt((p-q).dot(p-q));
}
vector<P> data;

vector<P> convex_hull(vector<P>& ps, int rm){
	int k = 0; //凸包頂點數
	vector<P> qs(n * 2); //建構中的凸包
	//建構下側凸包
	for(int i = 0; i < n; i++){
		if(i != rm){
			ps[i].id = i;
			while(k > 1 && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
			qs[k++] = ps[i];
		}
	}
	half_point = k-1;
	//建構上側凸包
	for(int i = n - 2, t = k; i >= 0; i--){
		if(i != rm){
			while(k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
			qs[k++] = ps[i];
		}
	}
	qs.resize(k-1);
	return qs;
}
double area_calc(vector<P>& ps){
	double area = 0.0;
	for(int i = 2; i < ps.size(); i++){
		area += (ps[i-1] - ps[0]).det(ps[i]-ps[0]);
	}
	return (area == 0.0 ? INF : area) ;
}
void solve(){
	sort(data.begin(), data.end());
	vector<P> qs = convex_hull(data, n);
	double res = INF;
	for(int i = 0; i < qs.size(); i++){
		vector<P> ps = convex_hull(data, qs[i].id);
		res = min(res, area_calc(ps));
	}
	printf("%.2f\n", res/2);  
}
void init(){
	data.clear();
}
int main(){
	while(cin>>n){
		if(n == 0) break;
		init();
		for(int i = 0; i < n; i++){
			double x, y;
			scanf("%lf %lf", &x, &y);
			data.push_back(P(x, y));
		}
		solve();
	}
	return 0;
}
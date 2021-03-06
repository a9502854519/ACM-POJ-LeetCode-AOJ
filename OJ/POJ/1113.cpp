#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
#define EPS 1E-10
#define INF 1E10
using namespace std;

int n;
double L;
const double pi = acos(-1);
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
	bool operator < (const P& other) const{
		if(x != other.x) return x < other.x;
		return y < other.y;
	}
};
double dist(P p, P q){
	return sqrt((p-q).dot(p-q));
}
vector<P> data;

vector<P> convex_hull(vector<P>& ps){
	sort(ps.begin(), ps.end());
	int k = 0; //凸包頂點數
	vector<P> qs(n * 2); //建構中的凸包
	//建構下側凸包
	for(int i = 0; i < n; i++){
		while(k > 1 && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	//建構上側凸包
	for(int i = n - 2, t = k; i >= 0; i--){
		while(k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k);
	return qs;
}
int solve(){
	vector<P> qs = convex_hull(data);
	/*for(int i = 0; i < qs.size(); i++){
		printf("(%.1f, %.1f)\n", qs[i].x, qs[i].y);
	}*/
	/*逆時針遍歷每個點，計算邊的長度總和*/
	double total_length = 0;
	for(int i = 1; i < qs.size(); i++){
		//計算邊的長度
		total_length += dist(qs[i], qs[i-1]);
	}
	total_length += 2*L*pi;
	int res = (int)total_length;
	if(total_length - (double)res > 0.5-EPS) res++;
	return res;
}
	
int main(){
	scanf("%d%lf", &n, &L);
	for(int i = 0; i < n; i++){
		double x, y;
		scanf("%lf%lf", &x, &y);
		data.push_back(P(x, y));
	}
	printf("%d\n", solve());
	return 0;
}
	
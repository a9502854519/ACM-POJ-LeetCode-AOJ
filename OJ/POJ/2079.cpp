#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
#define EPS 1E-10
#define INF 1E10
using namespace std;

int n, half_point;
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
	half_point = k-1;
	//建構上側凸包
	for(int i = n - 2, t = k; i >= 0; i--){
		while(k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
		qs[k++] = ps[i];
	}
	qs.resize(k);
	return qs;
}
void init(){
	data.clear();
}
double solve(){
	if(n < 3) return 0;
	double res = 0;
	vector<P> qs = convex_hull(data);
	for(int k = 1; k < qs.size()-1; k++){
		double last = -INF;
		for(int i = 0 ; i+k < qs.size()-1; i++){
			int ub, lb, mid, a, b, j = i+k;
			double tangent = (qs[j] - qs[i]).y/(qs[j] - qs[i]).x;
			if(tangent < last || last == -INF){
				ub = half_point, lb = -1;
				while(ub - lb > 1){
					mid = (ub+lb)/2;
					if((qs[mid+1] - qs[mid]).y/(qs[mid+1] - qs[mid]).x >= tangent) ub = mid;
					else lb = mid;
				}
				a = ub;//下半部的
				lb = half_point, ub = qs.size();
				while(ub - lb > 1){
					mid = (ub + lb)/2;
					if((qs[mid] - qs[mid-1]).y/(qs[mid]-qs[mid-1]).x <= tangent) lb = mid;
					else ub = mid;
				}
				b = lb;//上半部的
			}else{
				while((qs[a+1] - qs[a]).y/(qs[a+1] - qs[a]).x < tangent) a++;
				while((qs[b+1] - qs[b]).y/(qs[b+1] - qs[b]).x < tangent&& b < qs.size()-1) b++;
			}
			last = tangent;
			double area = abs((qs[j] - qs[i]).det(qs[a] - qs[i]))*0.5;
			res = max(res, area);
			area = abs((qs[j]-qs[i]).det(qs[b] - qs[i]))*0.5;
			res = max(res, area);
			//printf("(%d, %d), res = %.2f\n", i, j, res);
		}
	}
	return res;
}
int main(){
	while(cin>>n){
		if(n == -1) break;
		init();
		for(int i = 0; i < n; i++){
			double x, y;
			scanf("%lf %lf", &x, &y);
			data.push_back(P(x, y));
		}
		printf("%.2f\n",solve());
	}
	return 0;
}
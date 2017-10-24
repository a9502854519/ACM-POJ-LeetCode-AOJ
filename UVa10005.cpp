#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
#define EPS 1E-10
#define INF 1E10
#define MAX_N 99

using namespace std;

int n;

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

const double pi = acos(-1);
vector<P> data;
int R;

void init(){
	data.clear();
}

P calc_center(P a, P b, double d){
	
}
bool solve(){
	vector<P> ps = convex_hull(data);
	n = data.size();
	/*bool ok = true;
	for(int i = 0; i < n - 1; i++){
		double d = dist(ps[i], ps[i+1]);
		if(d > R + EPS) return false;
		
	}*/
}
int main(){
	while(cin>>n){
		if(!n) break;
		for(int i = 0; i < n; i++){
			int a, b;
			cin>>a>>b;
			data.push_back(P(a, b));
		}
		cin>>R;
		if(solve()){
			cout<<"The polygon can be packed in the cicle\n";
		}else{
			cout<<"There is no way of packing that polygon\n";
		}
	}
	return 0;
}
		
	
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<iostream>
#include<algorithm>
#define EPS 1E-10
#define INF 1E99

using namespace std;

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

int N, M;
vector<P> S1, S2;

void init(){
	S1.clear();
	S2.clear();
}
vector<P> convex_hull(vector<P>& ps){
	
	int n = ps.size();
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

void solve(){
	vector<P> C1 = convex_hull(S1);
	vector<P> C2 = convex_hull(S2);
	for(int i = 0; i < C2.size(); i++){
		//printf("(%.2f, %.2f)\n", C2[i].x, C2[i].y);
	}
	S1.clear(), S2.clear();
	P origin = C1[0]+C2[0];
	vector<P>& ps = S1, &qs = S2;
	for(int i = 0, j = 0; i < C1.size()-1 || j < C2.size()-1; ){
		P t1 , t2;
		//printf("i = %d  j = %d\n", i, j);
		if(i < C1.size()-1) t1 = C1[i+1] - C1[i]; 
		if(j < C2.size()-1) t2 = C2[j+1] - C2[j];
		if(i < C1.size() - 1 && (t1.det(t2) > 0 || j == C2.size()-1)){
			qs.push_back(t1);
			i++;
		}else if(j < C2.size()-1){
			qs.push_back(t2);
			j++;
		}
		//printf("t1 = (%.2f, %.2f)   t2 = (%.2f, %.2f)\n", t1.x, t1.y, t2.x, t2.y);
	}
	C1.clear(), C2.clear();
	C1.resize(0), C2.resize(0);
	for(int i = 0; i < qs.size(); i++){
		ps.push_back(origin);
		origin = origin + qs[i];
	}
	qs.clear();
	double res = INF;
	P o = P(0.0, 0.0);
	//cout<<endl<<endl;
	for(int i = 0; i < ps.size(); i++){
		//printf("(%.2f, %.2f)\n", ps[i].x, ps[i].y);
		res = min(res, dist(o, ps[i]));
		//printf("res = %.5f\n", res);
		if(i < ps.size()-1){
			if((ps[i+1]-ps[i]).dot(o-ps[i]) >= 0 && (ps[i]-ps[i+1]).dot(o-ps[i+1]) >= 0){
				res = min(res, (abs((ps[i+1]-ps[i]).det(o-ps[i]))/dist(ps[i+1], ps[i])));
				//printf("res = %.5f\n\n", res);
			}
		}
		
	}
	printf("%.5f\n", res);
}
int main(){
	while(scanf("%d %d\n", &N, &M) != EOF){
		if(!N&&!M) break;
		init();
		for(int i = 0; i < N; i++){
			double x, y;
			scanf("%lf %lf\n", &x, &y);
			S1.push_back(P(x, y));
		}
		for(int i = 0; i < M; i++){
			double x, y;
			scanf("%lf %lf\n", &x, &y);
			S2.push_back(P(-x, -y));
			//printf("(%.2f, %.2f)\n", -x, -y);
		}
		for(int i = 0; i < S1.size(); i++){
			for(int j = 0; j < S2.size(); j++){
				//printf("(%.2f, %.2f)\n", (S1[i]+S2[j]).x, (S1[i]+S2[j]).y);
			}
		}
		//cout<<"\n\n\n";
		solve();
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<utility>
#define MAX_N 1000000
#define INF 1E20
#define EPS 1E-10

using namespace std;
typedef pair<double, double> P;

P A[MAX_N];
int N;

bool compare_y(const P& a, const P& b){
	return a.second < b.second;
}
double min_perimeter(P *a, int n){
	if(n <= 2){
		sort(a, a + n, compare_y);
		return INF; //三角形最少要有三個點
	}
	int m = n / 2;
	
	double x = a[m].first; //中心線
	double d = min(min_perimeter(a, m), min_perimeter(a + m, n - m));
	inplace_merge(a, a + m, a + n, compare_y); //以y座標排序
	
	vector<P> b; //加入與直線距離不滿 d / 2 的點
	for(int i = 0; i < n; i++){
		if(fabs(a[i].first - x) < d / 2 + EPS){
			for(int j = b.size() - 1; j >= 0; j--){
				double dx = a[i].first - b[j].first;
				double dy = a[i].second - b[j].second;
				if(dy > d / 2 + EPS) break;
				
				for(int k = j - 1; k >= 0; k--){ 
					double dx1 = a[i].first - b[k].first;
					double dy1 = a[i].second - b[k].second;
					double dx2 = b[j].first - b[k].first;
					double dy2 = b[j].second - b[k].second;
					
					if(dy1 > d / 2 + EPS) break;
					
					double tmp = sqrt(dx * dx + dy * dy) +
								 sqrt(dx1 * dx1 + dy1 * dy1) +
								 sqrt(dx2 * dx2 + dy2 * dy2);
					
					d = min(tmp, d);
				}
			}
			b.push_back(a[i]);
		}
	}
	return d;
}
double solve(){
	sort(A, A + N); //以x座標排序
	printf("%.9f\n", min_perimeter(A, N));
}
int main(){
	int T;
	cin>>T;
	for(int i = 1; i <= T; i++){
		cin>>N;
		for(int i = 0; i < N; i++){
			scanf("%lf %lf\n", &A[i].first, &A[i].second);
		}
		printf("Case #%d: ", i);
		solve();
	}
}
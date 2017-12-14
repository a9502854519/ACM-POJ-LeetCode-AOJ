#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_N 10000

using namespace std;

struct P{
	int x, y;
	P () {}
	P (int x, int y) : x(x), y(y) {}
	bool operator == (const P& other) const{
		return x == other.x && y == other.y;
	}
};
vector<P> data, res;
vector<int> xs;
int n;

bool cmp(const P& a, const P& b){
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
void compress(){
	for(int i = 0; i < n; i++){
		xs.push_back(data[i].x);
	}
	sort(xs.begin(), xs.end());
	sort(data.begin(), data.end(), cmp);
	for(int i = 0; i < n; i++){
		data[i].x = lower_bound(xs.begin(), xs.end(), data[i].x) - xs.begin();
	}
}
void superset(int a, int b){ //[a, b)
	if(b - a <= 1) return;
	superset(a, (a + b) / 2);
	superset((a + b) / 2, b);
	vector<int> tmp;
	for(int i = 0; i < n && data[i].x < b; i++){
		if(data[i].x >= a){
			tmp.push_back(data[i].y);
		}
	}
	sort(tmp.begin(), tmp.end());
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	int x = xs[(a + b) / 2];//原始的座標
	for(int i = 0; i < tmp.size(); i++){
		res.push_back(P(x, tmp[i]));
	}
}
void solve(){
	compress();
	superset(0, xs.size());
	sort(res.begin(), res.end(), cmp);
	res.erase(unique(res.begin(), res.end()), res.end());
	printf("%d\n", res.size());
	for(int i = 0; i < res.size(); i++){
		printf("%d %d\n", res[i].x, res[i].y);
	}
}
int main(){
	cin>>n;
	for(int i = 0; i < n; i++){
		int x, y;
		scanf("%d %d\n", &x, &y);
		data.push_back(P(x, y));
		res.push_back(P(x, y));
	}
	solve();
	return 0;
}
	
	
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;

int n, W, H;
const long long int INF = 9223372036854775807;
struct p{
	int x, y;
	long long int c;
	p() {}
	p(int x, int y, long long int c) : x(x), y(y), c(c) {}
};
vector<p> stars;

bool sort_x(const p& a, const p& b){
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}
bool sort_y(const p& a, const p& b){
	if(a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}
void init(){
	stars.clear();
}
long long int calc(vector<p> part){
	sort(part.begin(), part.end(), sort_y);
	long long int res = -INF, temp = 0;
	int left = part[0].y, right = left ,i = 0, j = 0;
	do{
		//上側掃描線
		while(j < part.size() && right - left < H){
			temp += part[j++].c;
			if(j < part.size() && part[j].y > right) right = part[j].y;
		}
		if(temp > res) res = temp;
		//下側掃描線
		while(i < part.size() && right - left >= H){
			temp -= part[i++].c;
			if(i < part.size() && part[i].y > left) left = part[i].y;
		}
	}while(j < part.size());
	return res;
}
long long int solve(){
	sort(stars.begin(), stars.end(), sort_x);
	vector<p> y;
	long long int res = -INF, temp;
	int left = stars[0].x, right = left, i = 0, j = 0;
	do{
		//右側掃描線
		while(j < n && right - left < W){
			y.push_back(stars[j]);
			if(++j < n && stars[j].x > right) right = stars[j].x;
		}
		temp = calc(y);
		if(temp > res) res = temp;
		while(i < n && right - left >= W){
			y.erase(y.begin());
			if(++i < n && stars[i].x > left) left = stars[i].x;
		}
	}while(j < n);
	return res;
}
int main(){
	while(scanf("%d%d%d", &n, &W, &H) != EOF){
		init();
		for(int i = 0; i < n; i++){
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			stars.push_back(p(x, y, c));
		}
		//printf("%lld\n",solve());
		cout<<solve()<<endl;
	}
	return 0;
}
		
	
	
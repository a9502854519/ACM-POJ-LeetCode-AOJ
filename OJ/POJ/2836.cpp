#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#define INF 1E9
using namespace std;

int n;
int dp[1<<15];
struct Data{
	int x, y;
}data[15];

class Rec{
	private:
		int set;
		int area;
	public:
		Rec(){
			set = 0;
			area = 0;
		}
		void add(int i){
			set |= (1<<i);
		}
		void calc_area(int x1, int y1, int x2, int y2){
			area = (y2-y1)*(x2-x1);
		}
		int get_set(){
			return set;
		}
		int get_area(){
			return area;
		}	
};
vector<Rec> rec;

void make_rec(){
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			Rec r;
			r.add(i);
			r.add(j);
			int x1 = min(data[i].x, data[j].x), y1 = min(data[i].y, data[j].y);
			int x2 = max(data[i].x, data[j].x), y2 = max(data[i].y, data[j].y);
			if(x1 == x2) x2++;
			else if (y1 == y2) y2++;
			r.calc_area(x1, y1, x2, y2);
			for(int m = 0; m < n; m++){
				if(m != i && m != j){
					if(x1 <= data[m].x && data[m].x <= x2 && y1 <= data[m].y && data[m].y <= y2){
						r.add(m);
					}
				}
			}
			rec.push_back(r);
		}
	}
}
void out(int s){
	for(int i = 14; i >=0; i--){
		printf("%d",( (s>>i) & 1) ? 1 : 0);
	}
	cout<<endl;
}
int main(){
	while(cin>>n){
		fill(dp, dp+(1<<15), INF);
		rec.clear();
		if(n == 0) break;
		for(int i = 0; i < n; i++){
			scanf("%d%d", &data[i].x, &data[i].y);
		}
		make_rec();
		/*for(int i = 0; i < rec.size(); i++){
			int set = rec[i].get_set();
			int area = rec[i].get_area();
			printf("area : %d  set : ", area);
			out(set);
		}*/
		dp[0] = 0;
		for(int S = 1; S < (1<<n); S++){
			for(int i = 0; i < rec.size(); i++){
				int set = rec[i].get_set(), area = rec[i].get_area();
				dp[S] = min(dp[S], dp[S^(S&set)]+area);
			}
		}
		cout<<dp[(1<<n)-1]<<endl;
		
	}
	return 0;
}
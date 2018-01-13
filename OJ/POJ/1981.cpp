#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#define EPS 1E-4
#define MAX_N 300
using namespace std;

struct p{
	double x, y; 
	bool operator < (const p& other) const{
		return y < other.y;
	}
};
p data[MAX_N];
int N;

int calc(double cx1, double cy1, double cx2, double cy2){
	double x, y;
	int sum1 = 0, sum2 = 0;
	for(int i = 0; i < N; i++){
		x = data[i].x, y = data[i].y;
		double d;
		if(abs(y-cy1) < 1+EPS){
			d = sqrt((x-cx1)*(x-cx1)+(y-cy1)*(y-cy1));
			if(d < 1+EPS) sum1++;
		}
		if(abs(y-cy2) < 1+EPS){
			d = sqrt((x-cx2)*(x-cx2)+(y-cy2)*(y-cy2));
			if(d < 1+EPS) sum2++;
		}
		else if (y > max(cy1, cy2)+1+EPS){
			break;
		}
	}
	return sum1 > sum2 ? sum1 : sum2;
}
int solve(){
	sort(data, data+N);
	int res = 1;
	for(int i = 0; i < N; i++){
		for(int j = i+1; j < N; j++){
			double x1 = data[i].x, y1 = data[i].y,
				   x2 = data[j].x, y2 = data[j].y;
			double d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
			if(d < 2-EPS){
				//計算圓心
				double x3 = (x1+x2)/2, y3 = (y1+y2)/2;//取中心點
				d = sqrt(1-d*d/4);//取圓心與中心點的距離
				double vx = y2-y1, vy = x1-x2;//圓心和中心點形成的向量
				double vd = sqrt(vx*vx+vy*vy);//向量的長度
				double cx1 = x3+vx*(d/vd), cy1 = y3+vy*(d/vd),//第一組圓心
					   cx2 = x3-vx*(d/vd), cy2 = y3-vy*(d/vd);//第二組圓心
				int count = calc(cx1, cy1, cx2, cy2); //計算有多少個點在圓內
				res = max(count, res);
			}
		}
	}
	return res;
}

int main(){
	while(cin>>N){
		if(!N) break;
		double x, y;
		for(int i = 0; i < N; i++){
			scanf("%lf%lf", &data[i].x, &data[i].y);
		}
		cout<<solve()<<endl;;
	}
	return 0;
}
	
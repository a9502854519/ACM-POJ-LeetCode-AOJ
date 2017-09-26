#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
#define MAX_N 100
#define EPS 5.1E-13
using namespace std;

const double pi = 3.141592653589793238462643383;
struct R{
	double x, y, r;
	R() {}
	R(double x, double y, double r) : x(x), y(y), r(r){
	}
};
vector<R> data;
vector<double> confetti[MAX_N];
int n;
bool isOK[MAX_N];
bool isCovered[MAX_N];
void init(){
	data.clear();
	for(int i = 0; i < n; i++) confetti[i].clear();
}
void calc(int i, int j){
	double x1 = data[i].x, y1 = data[i].y, r1 = data[i].r,
		   x2 = data[j].x, y2 = data[j].y, r2 = data[j].r;
	double d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	double L1 = (r1*r1 - r2*r2 + d*d) / (2*d),
		   L2 = (r2*r2 - r1*r1 + d*d) / (2*d);
	d = sqrt(r1*r1 - L1*L1);
	double theta1 = atan(d/L1), theta2 = atan((y1-y2)/(x1-x2));
	if((theta2 > 0-EPS && y2 < y1) || (theta2 < 0+EPS && x2 < x1)) theta2 += pi;
	confetti[i].push_back(theta2+theta1); confetti[i].push_back(theta2-theta1);
	theta1 = atan(d/L2), theta2 = atan((y2-y1)/(x2-x1));
	if((theta2 > 0-EPS && y1 < y2) || (theta2 < 0+EPS && x1 < x2)) theta2 += pi;
	confetti[j].push_back(theta2+theta1); confetti[j].push_back(theta2-theta1);
}
		
void solve(){
	//計算兩兩的交點
	memset(isCovered, false, sizeof(isCovered));
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			//確認兩圓相交情況
			double x1 = data[i].x, y1 = data[i].y, r1 = data[i].r,
				   x2 = data[j].x, y2 = data[j].y, r2 = data[j].r;
			double d = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
			/*if(i == 1 && j == 2){
				printf("y1 = %.100f\ny2 = %.100f\n", y1, y2);
				printf("d  = %.200f  r2 - r1 = %.200f\n", d, r2-r1);
				printf("%d\n", abs(r2-r1) >= d-EPS);
			}*/
			
			if(r2-r1 >= d-EPS){
				isCovered[i] = true;
			}else if(d <= r1+r2+EPS){
				//求兩圓交點
				calc(i, j);
			}
		}
		if(confetti[i].size() > 0) confetti[i].push_back(confetti[i][0]+2*pi);
		
	}
	/*for(int i = 0; i < n; i++){
		for(int j = 0; j < confetti[i].size(); j++){
			printf("%.5f ", confetti[i][j]*180/pi);
		}
		cout<<endl;
	}*/
	memset(isOK, false, sizeof(isOK));
	isOK[n-1] = true;//最上面的一定可見
	for(int i = n - 1; i >= 0; i--){
		if(!isCovered[i] && confetti[i].size() > 0){
			for(int j = 0; j < confetti[i].size()-1; j++){
				double theta = (confetti[i][j]+confetti[i][j+1])/2;
				double x = data[i].x, y = data[i].y, r = data[i].r+EPS;
				x += cos(theta)*r, y += sin(theta)*r;
				bool touched = false;
				for(int k = n-1; k >= 0; k--){
					if(i != k && !isCovered[k]){
						double x1 = data[k].x, y1 = data[k].y, r1 = data[k].r;
						if(sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)) <= r1-EPS){
							isOK[k] = true;
							touched = true;
							break;
						}
					}
				}
				if(!touched) isOK[i] = true;
			}
		}
	}
	int res = 0;
	for(int i = 0; i < n; i++){
		//printf("%d is %s\n", i, (isOK[i] ? "visible" : "unvisible"));
		//res += isOK[i];
		if(isOK[i] || (confetti[i].size() == 0 && !isCovered[i])){
			res++;
		}
	}
	printf("%d\n", res);
}	
				
int main(){
	while(cin>>n){
		if(!n) break;
		init();
		for(int i = 0; i < n; i++){
			double x, y, r;
			scanf("%lf%lf%lf", &x, &y, &r);
			data.push_back(R(x, y, r));
		}
		solve();
	}
	return 0;
}
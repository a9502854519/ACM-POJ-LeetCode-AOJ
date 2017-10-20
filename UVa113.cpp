#include<iostream>
#include<cstdio>
#include<cmath>
#define EPS 1E-12
using namespace std;

int n;
double p;

void solve(){
	double x = 0, y = 2;
	while(abs(y - x) > EPS){
		x = y;
		y = ((n-1) * x + p / pow(x, n-1)) / n;
	}
	printf("%.0f\n", y);
}
int  main(){
	while(cin>>n>>p){
		solve();
	}
	return 0;
}

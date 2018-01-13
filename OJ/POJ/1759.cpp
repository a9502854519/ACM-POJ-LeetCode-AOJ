#include<iostream>
#define EPS 1E-6
#include<cstdio>

using namespace std;

int N;
double A, B;

bool C(double y){
	double z, x = A;
	for(int i = 0; i < N-2; i++){
		z = (y+1)*2-x;
		if(!(z > 0 + EPS)) return false;
		x = y;
		y = z;
	}
	B = z;
	return true;
}
int main(){
	cin>>N>>A;
	double ub = A, lb = 0, mid;
	for(int i = 0; i < 100; i++){
		mid = (ub + lb)/2;
		if(C(mid)) ub = mid;
		else lb = mid;
	}
	printf("%.2f\n", B);
	return 0;
}
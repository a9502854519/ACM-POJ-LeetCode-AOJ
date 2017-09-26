#include<iostream>
#include<algorithm>
#include<cstdio>
#define INF 1E9
using namespace std;

int N, M;
int money[100000];

bool C(int limit){
	int m = M;
	for(int i = 0; i < N;){
		int sum = 0;
		for(;i <= N-m; i++){
			if(money[i] > limit){
				return false;
			}
			sum += money[i];
			if(sum > limit)
				break;
		}
		if( --m == 0 && i <N-1){
			return false;
		}
	}
	return true;
}

int main(){
	cin>>N>>M; //n個月，m個區間
	int lb = INF, ub = 0, mid;
	for(int i = 0 ; i < N; i++){
		cin>>money[i];
		lb = min(lb, money[i]);
		ub += money[i];
	}
	
	while(ub - lb > 1){
		mid = (ub + lb) / 2;
		if(C(mid)) ub = mid;
		else lb = mid;
	}
	cout<<ub<<endl;
	return 0;
}
	
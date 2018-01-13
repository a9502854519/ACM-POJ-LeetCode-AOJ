#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

int X[50000];
int n,m;

bool C(int k){
	int sum = 0, temp;
	for(int i = 0; i < n; i++){
		int val = X[i] + k;
		temp = n - (lower_bound(X, X + n, val) - X);
		if(temp == 0) break;
		sum+=temp;
	}
	return sum > m/2;
}
int solve(){
	sort(X, X+n);
	int ub = X[n-1] - X[0] + 1, lb = 0, mid;
	m = (n-1)*n/2; //中位數的個數
	while(ub - lb > 1){
		mid  = (ub + lb) / 2;
		if(C(mid)) lb = mid;
		else ub = mid;
	}
	return lb;
}
int main(){
	while(cin>>n){
		for(int i = 0; i<n; i++){
			scanf("%d", &X[i]);
		}
		printf("%d\n", solve());
	}		
	
	return 0;
}
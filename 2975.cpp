#include<iostream>
#include<cstdio>
#define MAX_N 1000

using namespace std;

int n, x;
int A[MAX_N];

int solve(){
	if(x == 0) return 0;
	int res = 0;
	for(int i = 0; i < n; i++){
		res += (A[i] ^ x) < A[i];
	}
	return res;
}
int main(){
	while(cin>>n){
		if(!n) break;
		x = 0;
		for(int i = 0; i < n; i++){
			scanf("%d", A+i);
			x ^= A[i];
		}
		printf("%d\n", solve());
	}
	return 0;
}
		



#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 10
using namespace std;

int n;
int A[MAX_N];
bool solve(){
	int x = 0, c;
	for(int i = 0; i < n; i++){
		scanf("%d", A+i);
	}
	if((n & 1)) return true;

	sort(A, A+n);
	for(int i = 0; i < n; i += 2){
		if(A[i] != A[i+1]) return true;
	}
	return false;
}
int  main(){
	while(cin>>n){
		if(!n) break;
		printf("%d\n", (int)solve());
	}
	return 0;
}


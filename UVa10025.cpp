#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

long long k;

long long  solve(){
	k = abs(k);
	int n = -ceil((-1 - sqrt(8*k)) / 2), sum;
	while(((sum = n * (n + 1) / 2) - k) & 1 || sum == 0){
		n++;
	}
	return n;
}
int main(){
	int C;
	cin>>C;
	while(C--){
		cin>>k;
		printf("%lld\n", solve());
		if(C > 0) printf("\n");
	}
	return 0;
}
		
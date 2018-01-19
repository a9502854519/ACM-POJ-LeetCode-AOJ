#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 1E18
#define MOD 1000000007

using namespace std;
typedef unsigned long long ull;

ull n, m, k;

void swap(ull a, ull b){
	a ^= b;
	b ^= a;
	a ^= b;
}
ull exp_mod(ull a, ull b){
	ull A = a % MOD, res = 1;
	while(b > 0){
		if(b & 1) res = res * A % MOD;
		A = A * A % MOD;
		b >>= 1;
	}
	return res;
}
ull solve(){
	if(m < n) swap(n, m);
	if(k == -1 && ((n ^ m) & 1)){
		return 0;
	}else{
		return exp_mod(exp_mod(2, n - 1), m - 1);
	}
}
int main(){
	cin >> n >> m >> k;
	cout << solve() << endl;
	return 0;
}

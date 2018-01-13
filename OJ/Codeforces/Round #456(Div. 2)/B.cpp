#include<iostream>
#include<cstdio>

using namespace std;
typedef  long long ll;
ll n, k;

ll solve(){
	int m;
	for(m = 0;; m++){
		if((1ll << m) > n) break;
	}
	m--;
	ll res;
	if(k > 1) res = (1ll << m) + (1ll << m) - 1;
	else res = n;
	return res;
}
int main(){
	cin >> n >> k;
	cout << solve() << endl;
	return 0;
}
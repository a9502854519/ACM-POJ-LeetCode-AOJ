#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;
typedef long long ll;

ll n;
const ll m = 3;

ll  gcd(ll a, ll b){
	if(b == 0) return a;
	return gcd(b, a % b);
}
ll poww(ll a, ll b){
	ll d = 1, c = a;
	while(b > 0){
		if(b & 1){
			d = d * c;
		}
		b >>= 1;
		c = c * c;
	}
	return d;
}
		
int solve(){
	if(n == 0) return 0;
	ll res = poww(m, n);
	for(int k = 1; k < n; k++){
		res += poww(m, gcd(n, k));
	}
	if(n & 1){
		res += m * poww(m, (n-1)/2) * n;
	}else{
		res += (m*m * poww(m, (n-2)/2) * n / 2)
 	  	     + (poww(m, n/2) * n / 2);
	}
	return res/(2*n);
}

int main(){
	while(cin>>n){
		if(n == -1) break;
		cout<<solve()<<endl;
	}
	return 0;
}

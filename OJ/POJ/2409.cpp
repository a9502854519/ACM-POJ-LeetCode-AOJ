#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int n, m;

int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a % b);
}
int  solve(){
	if(n == 0) return 0;
	int res = 0;
	for(int k = 0; k < n; k++){
		res += pow(m, gcd(k, n));
	}
	if(n & 1){
		res += m * pow(m, (n-1)/2) * n;
	}else{
		res += (m*m * pow(m, (n-2)/2) * n / 2)
 	  	     + (pow(m, n/2) * n / 2);
	}
	return res/(2*n);
}

int main(){
	while(cin>>m>>n){
		if(!n && !m) break;
		cout<<solve()<<endl;
	}
	return 0;
}
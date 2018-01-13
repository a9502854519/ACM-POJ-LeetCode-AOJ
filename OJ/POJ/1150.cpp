#include<iostream>
#include<cstdio>
#include<cmath>
#define MAX_P 5
using namespace std;

int N, M;
int fact[MAX_P];
int mod2_inverse[4] = {-2, -1, 2 ,1};
void init(){
	fact[0] = 1;
	for(int i = 1; i < MAX_P; i++){
		fact[i] = (fact[i-1]*i)%MAX_P;
	}
}

/*int exp_mod(int a, int b, int p){// a^b mod p
	int d = 1;
	while(b > 0){
		d = (d*d) % p;
		if(b & 1){
			d = (d * a) % p;
		}
		b >>= 1;
	}
	return d;
}*/
int extgcd(int a, int b, int& x, int& y){
	int d = a;
	if(b != 0){
		d = extgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}else{
		x = 1, y = 0;
	}
	return d;
}
int mod_fact(int n, int p, int& e){
	e = 0;
	if(n == 0) return 1;
	
	int res = mod_fact(n/p, p, e);
	e += n/p;
	if(n / p % 2 != 0) return res * (p - fact[n % p]) % p;
	return res * fact[n % p] % p;
}
int mod_fact_factorial(int n, int m, int p, int& e){  //回傳P(n, m) = a*p^e 的e和a mod p
	int e1, e2, a1, a2, a;
	a1 = mod_fact(n, p, e1);  
	a2 = mod_fact(n-m, p, e2);
	//printf("a1 = %d  e1 = %d\n", a1, e1);
	//printf("a2 = %d  e2 = %d\n", a2, e2);
	int x, y;
	extgcd(a2, p, x, y);
	//a = (a1/a2) mod p
	e = e1 - e2, a = (a1 * x % p + p) % p;
	return a;
}
int solve(){
	init();
	int e1, a1, a2, e2;
	a1 = mod_fact_factorial(N, M, 5, e1);
	a2 = mod_fact_factorial(N, M, 2, e2);
	if(e1 <= e2){
		//對a1 取 2^e 的反元素
		int x;
		if(e1 > 0) x = mod2_inverse[(e1-1) % 4];
		else x = -4;

		a1 = (a1 * x % 5 + 5) % 5;
		if(e1 == e2){
			return a1 + 5 * !(a1 & 1);
		}else{
			return a1 + 5 * (a1 & 1);
		}
	}else{
		if(a2 & 1) return 5;
		else return 0;
	}	
}
int main(){
	while(cin>>N>>M){
		printf("%d\n", solve());
	}
	return 0;
}
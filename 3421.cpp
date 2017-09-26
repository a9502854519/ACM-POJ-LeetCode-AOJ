#include<iostream>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>
#define MAX_PRIME 1024
using namespace std;

typedef unsigned long long int ull;
typedef const unsigned long long int cull;
enum number{composite = 0, prime = 1};
ull INF ((1<<63) - 1);
bool is_prime[1025];
long long int sprp[12] = {2,3,5,7,11,13,17,19,23,29,31,37};

ull gcd(ull a, ull b){
    while (b){
        ull c = a % b;
         a = b;
         b = c;
     }
    return a;
}

void init(){
	fill(is_prime, is_prime+MAX_PRIME, true);
	is_prime[0] = false, is_prime[1] = false, is_prime[2] = true;
	for(int i = 2; i<=MAX_PRIME; i++){
		if(is_prime[i]){
			for(int j = i*2;j<=MAX_PRIME; j+=i){
				is_prime[j] = false;
			}
		}
	}
}

ull multi(ull a, ull b, ull n){ //a * b mod n
	ull temp = 0;
	a %= n;
	for(int i = 63; i>=0; i--){
		if((b >>i) & 1){
			temp += a;
			temp %= n;
		}
		temp <<= 1;
		temp %= n;
	}
	return temp;
}

ull pollard_rho(cull n, cull c){
	int i = 1;
	int x = 2;
	int y = x;
	int d;
	int k = 2;
	while(true){
		x = ((x, x, n) + c % n) % n;//(x*x + c) % n;
		d = gcd((x > y ? x - y : y - x), n);
	
		if(d > 1 && d <= n)
		 	return d;
		if(++i == k){
			y = x;
			k<<=1;
		}
	}  
}

ull MODULAR_EXP(ull a, ull b, ull n){//a^n-1 mod n 

	ull d = 1;
	
	for(int i= 63; i>=0; i--){
		d = multi(d, d, n);//(d * d) % n;
		if((b>>i) & 1){
			d = multi(d, a, n);//(d * a) % n;
		}
	}
	return d;
}

number witness(ull a, ull n){
	ull u = n-1, t = 0;
	
	while(!(u & 1)){
	 	u>>=1;
	  	t++;
	}
	ull x = MODULAR_EXP(a, u, n); 
	for(int i = 1; i<=t; i++){
		
		ull y = multi(x, x, n);//(x * x) % n;
	 	if(y == 1 && x != 1 && x != n-1)
			return composite; 
		x = y;
	}
	if(x != 1)
		return composite; 
	return prime; 
}

bool MILLAR_RABIN(ull n){
	
	for(int i=0; i<12; i++){
		ull a = sprp[i];
		if(witness(a, n) == composite)
			return composite; 
	}
	return prime; 
} 

bool isprime(ull n){
	if(n <= MAX_PRIME) return is_prime[n];
	else return MILLAR_RABIN(n);
}

vector<int> factor; 
vector<int> factor_count;
int total;
void factorize(ull n){ 
/*
 	if(n == 1) return;
 	if(isprime(n) == prime){
		total++;
		if(!factor.empty() && factor.back() == n){
			factor_count.back() ++;
		}else{
			factor.push_back(n);
			factor_count.push_back(1);
		}
 		return;
 	}
 	ull d = n;
 	for(int c = 0; d == n; c++){ 
	  d = pollard_rho(n, c);
	}
	factorize(d);
	factorize(n / d);*/
	for(int i = 2; i * i <= n; i++){
		if(is_prime[i] && n % i == 0){
			factor.push_back(i);
			factor_count.push_back(0);
			while(n % i == 0){
				total ++;
				factor_count.back()++;
				n /= i;
			}
		}
	}
	if(n != 1){
		total ++;
		factor.push_back(n);
		factor_count.push_back(1);
	}
}


ull factorial[21];
void init_fac(void){
	factorial[0] = 1, factorial[1] = 1;
	for(int i = 2; i<=20;i++){
		factorial[i] = factorial[i-1] * i;
	}
}
int main(){
	ull X;
	init();
	init_fac();
	srand(int(time(0)));
	while(cin>>X){
		factor.clear();
		factor_count.clear();
		total = 0;
		
		factorize(X);
		ull res = factorial[total];
		for(int i = 0; i<factor.size(); i++){
			res /= factorial[factor_count[i]];
		}
		cout<<total<<" "<<res<<endl;
		
	}
	return 0;
}
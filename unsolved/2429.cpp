#include<iostream>
#include<ctime>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_PRIME 200000 

using namespace std;
typedef unsigned long long int ull;
typedef const unsigned long long int cull;
enum number{composite = 0, prime = 1};
ull INF ((1<<63) - 1);

bool is_prime[200001];
long long int sprp[12] = {2,3,5,7,11,13,17,19,23,29,31,37};

/*int gcd(ull a, ull b){
	if(b == 0) return a;
	return gcd(b, a % b);
}*/
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
		temp <<= 1;
		temp %= n;
		if(((b >>i) & 1) == 1){
			temp += a;
			temp %= n;
		}
	}
	return temp;
}
		
ull pollard_rho(cull n, cull c){
	ull i = 1;
	ull x = 2;
	ull y = x;
	ull d;
	ull k = 2;
	while(true){
		//x = (multi(x, x, n) + c % n) % n;
		x = (x * x + c) % n;
		d = gcd((y - x > 0 ? y - x : x - y), n);
	
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
		//d = multi(d, d, n);
		d = (d * d) % n;
		if((b>>i) & 1){
			//d = multi(d, a, n);
			d = (d * a) % n;
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
	ull x = MODULAR_EXP(a, u, n); //璸衡a^u mod n
	for(int i = 1; i<=t; i++){
		
		ull y = multi(x, x, n);//(x * x) % n;
	 	if(y == 1 && x != 1 && x != n-1)
			return composite; //﹚琌计
		x = y;
	}
	if(x != 1)
		return composite; //﹚琌计
	return prime; //琌计琌借计
}

bool MILLAR_RABIN(ull n){
	
	for(int i=0; i<12; i++){
		ull a = sprp[i];
		if(witness(a, n) == composite)
			return composite; //琌计
	}
	return prime; //琌借计
} 

bool isprime(ull n){
	if(n <= MAX_PRIME) return is_prime[n];
	else return MILLAR_RABIN(n);
}

vector<ull> factor; 

ull mypow(ull a, ull b){
	ull d = 1;
	for(int i = 0; i < b; i++){
		d*=a;
	}
	return d;
}
		
void factorize(ull n){ 
	
 	if(isprime(n) == prime){
		
 		if(!factor.empty()){
			for(int i = 0; i<factor.size(); i++){
				if(factor[i] % n == 0){
					factor[i] *= n;
					n = -1;
					break;
				}
			}
		}
		if(factor.empty() || n != -1){
 			factor.push_back(n);
		}
 		return;
 	}
	/*if(t == 1){//代表需使用試除法，只需做一次即可
		for(ull i = 2; i<=1000 && n != 1; i++){
			if(is_prime[i] == true && n % i == 0){
				factor.push_back(i);
				n /= i;
				while(n % i == 0){
					factor.back() *= i;
					n/=i;
				}
			}
		}
	}
	if(n == 1) return ;*/
	
 	ull d = n;
	
 	for(int c = 0; d == n; c++){ 
	  d = pollard_rho(n, c);
	}
	
	factorize(d);
	factorize(n / d);
}

int main(){

	init();//﹍て借计 

	ull gcd, lcm, d;
	while(cin>>gcd>>lcm){
		//gcd = 3, lcm = 67553994410557440;
		factor.clear();
		
		
		if(lcm != gcd && lcm != 0 && gcd != 0){
			d = lcm / gcd;
			
			factorize(d); 
			
			ull a, b, res_a = 0, res_b = 0, res_sum = INF;
			int l = factor.size() - 1;
			for(unsigned int i = 1;i < (1<<l);i++){
				a = 1, b = 1;
				for(int j = 0; j < factor.size(); j++){
					if((i >> j) & 1 == 1)
						a *= factor[j];
					else
						b *= factor[j];
				}
				if(a + b < res_sum){
					res_sum = a+b;
					res_a = a*gcd;
					res_b = b*gcd;
				}
			}
			if(res_a < res_b)
				cout<<res_a<<" "<<res_b<<endl; 
			else 
				cout<<res_b<<" "<<res_a<<endl;
		}else{ 
			cout<<gcd<<" "<<gcd<<endl;
		}
	}
	
	
	return 0;
		
}

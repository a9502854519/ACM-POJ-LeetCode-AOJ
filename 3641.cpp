#include<iostream>
#include<ctime>
#include<cstdlib>
#define MAX_PRIME 200000

using namespace std;
typedef unsigned long long int ull;
typedef const unsigned long long int cull;
enum number{composite = 0, prime = 1};
ull INF ((1<<63) - 1);
bool is_prime[200001];
long long int sprp[3] = {2,7,61};

ull gcd(ull a, ull b){
    while (b){
        ull c = a % b;
         a = b;
         b = c;
     }
    return a;
}
void init(){
	fill(is_prime, is_prime+MAX_PRIME+1, true);
	is_prime[0] = false, is_prime[1] = false, is_prime[2] = true;
	for(int i = 2; i<=MAX_PRIME; i++){
		if(is_prime[i]){
			for(int j = i*2;j<=MAX_PRIME; j+=i){
				is_prime[j] = false;
			}
		}
	}
}
ull multi(ull a, ull b, ull n){
	ull temp = 0;
	for(int i = 63;i >=0; i--){
		temp <<= 1;
		temp %= n;
		if((b >> i) & 1 == 1){
			temp += a;
			temp %= n;
		}
	}
	return temp;
}
ull MODULAR_EXP(ull a, ull b, ull n){//a^b mod n 

	ull d = 1;
	
	for(int i= 63; i>=0; i--){
		//d = (d * d) % n;
		d = multi(d, d, n);
		if((b>>i) & 1 == 1){
			
			//d = (d * a) % n;
			d = multi(d, a, n);
			
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
		
		//ull y = (x * x) % n;
		ull y = multi(x, x, n);
	 	if(y == 1 && x != 1 && x != n-1)
			return composite; 
		x = y;
	}
	if(x != 1)
		return composite; 
	return prime; 
}

bool MILLAR_RABIN(ull n){
	
	for(int i=0; i<3; i++){
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

int main(){
	ull a, p;
	init();
	while(cin>>p>>a){
		if(p == 0 && a == 0) break;
		if(isprime(p) == prime){
			cout<<"no\n";
		}else{
			if(MODULAR_EXP(a, p, p) == a){
				cout<<"yes\n";
			}else{
				cout<<"no\n";
			}
		}
		
	}
	return 0;
}
		
		//這題的關鍵在於MODULAR_EXP，但目前，我對於這個函數的正確性，沒有十足的把握
		//所以未來的工作，就是對MODULAR_EXP除錯
	
		
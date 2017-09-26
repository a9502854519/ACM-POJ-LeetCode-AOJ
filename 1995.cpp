#include<iostream>
#include<utility>

using namespace std;
typedef unsigned long long int ull;



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

int main(){
	int Z;
	cin>>Z;
	ull M, H, res;
	ull A, B;
	for(int i =0 ;i<Z; i++){
		cin>>M>>H;
		res = 0;
		for(int j = 0; j<H; j++){
			cin>>A>>B;
			res += MODULAR_EXP(A, B ,M);
			res %= M;
		}
		cout<<res<<endl;
	}
	return 0;
}
		
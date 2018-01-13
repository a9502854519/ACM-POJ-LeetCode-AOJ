#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#define MAX_P 31624
using namespace std;

int N;
bool is_prime[MAX_P];
vector<int> prime;

void init(){
	fill(is_prime, is_prime+MAX_P, true);
	is_prime[0] = is_prime[1] = false;
	for(int i = 2; i < MAX_P; i++){
		if(is_prime[i]){
			for(int j = i; j < MAX_P; j += i){
				is_prime[j] = false;
			}
			prime.push_back(i);
		}
	}
}
vector<int> factorize(){
	vector<int> factor;
	int M = N;
	for(int i = 0; i < prime.size() && prime[i] < sqrt(N); i++){
		if(M % prime[i] == 0){
			factor.push_back(prime[i]);
			while(M % prime[i] == 0) M /= prime[i];
		}
	}
	if(M != 1) factor.push_back(M);
	return factor;
}
void solve(){
	vector<int> factor = factorize();
	int m = factor.size();
	int res = 0;
	for(int i = 1; i < (1<<m); i++){
		int t = 1, count = 0;
		for(int j = 0; j < m; j++){
			if((i>>j) & 1){
				t *= factor[j];
				count++;
			}
		}
		res += (N / t) * ((count & 1) ? 1 : -1);
	}
	printf("%d\n", N - res);
}
int main(){
	init();
	while(cin>>N){
		if(!N) break;
		solve();
	}
	return 0;
}

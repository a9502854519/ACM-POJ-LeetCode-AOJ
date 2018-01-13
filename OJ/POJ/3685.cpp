#include<iostream>
#include<cmath>
#include<cstdio>
//最後問題出在j沒有開long long ....
using namespace std;

long long int N, M;

bool C(long long int k){
	long long int sum = 0;
	long long int b,c;
	int res;
	for(long long int j = 1; j <= N; j++){
		b = 100000 + j;
		c = j*j - 100000*j - k;
		double right = (-b + sqrt(b*b - 4*c)) / 2;
		res = min((int)N, (int)floor(right));
		if(res > 0) sum+=res;
	}
	return sum >= M;
}
		
		
int main(){
	int T;
	long long int ub, lb, mid;                                                    
	cin>>T;

	for(int a = 0; a < T; a++){
		cin>>N>>M;
		if(N < 50000){
			ub = N*N+100000*N+1-100000+N;
			lb = 1 + 100000 + N*N - 100000*N + N - 1;
		}else{
			ub = 7500000000;
			lb = -4999700001-1;
		}
		while(ub - lb > 1){
			mid = (ub+lb)/2;
			if(C(mid)) ub = mid;
			else lb = mid;
		}
		cout<<ub<<"\n";
	}
	return 0;
}
		
	
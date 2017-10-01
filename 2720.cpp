#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define MAX_M 1000000
using namespace std;

int t[101][101];

int exp_mod(long long a, int b, int m){
	long long d = 1;
	while(b > 0){
		if(b & 1){
			d = d * a % m;
		}
		a = a * a % m;
		b >>= 1;
	}
	return d;
}
void init(){
	memset(t, -1, sizeof(t));
	//打表
	for(int i = 1; i <= 100; i++){
		t[i][0] = 1;
		int e = i;
		for(int j = 1; j <= 100; j++){
			t[i][j] = e;
			//e = i ^ e
			if(pow(i, e) > MAX_M) break;
			e = (int)pow(i, e);
		}
	}
}
int solve(int b, int i, int n){
	//euler_phi
	int e;
	if(n % 5 == 0) e = n * 2 / 5;
	else if(n > 1) e = n / 2; 
	else e = 1;
	
	if(t[b][i-1] == -1 || t[b][i-1] > e){
		int temp = solve(b, i-1, e)+e;
		return exp_mod(b, temp, n);
	}else{
		return exp_mod(b, t[b][i-1], n);
	}
}
int main(){
	init();
	int b, i, n;
	while(scanf("%d", &b)){
		if(b == 0) break;
		scanf("%d%d", &i, &n);
		int temp = 1;
		for(int j = 0; j < n; j++){
			temp *= 10;
		}
		int res = solve(b, i, temp);
		temp = res;
		int i = n;
		do{
			temp /= 10;
			i--;
		}while(temp > 0);
		while(i--){
			printf("0");
		}
		printf("%d\n", res);
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#define MAX_N 2000

using namespace std;

int n;
int a[MAX_N];
int b[MAX_N];

int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a % b);
}
void get(int &x, int &y){
	for(int k = 1; k < n; k++){
		for(int i = 0; i + k < n; i++){
			int j = i + k;
			int g = gcd(b[i], a[j]);
			if(g == 1){
				x = i, y = j;
				return;
			}
			b[i] = g;
		}
	}
	x = -1, y = -1;
}
int solve(){
	int x, y;
	get(x, y);
	if(x == -1 && y == -1){
		if(n == 1 && a[0] == 1) return 0;
		else return -1;
	}
	
	int res = 0;
	for(int i = x + 1; i < n; i++){
		if(a[i] != 1) res++;
	}
	for(int i = y - 1; i >= 0; i--){
		if(a[i] != 1) res++;
	}
	return res;
}
	
	
int main(){
	cin>>n;
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
		b[i] = a[i];
	}
	printf("%d\n", solve());
	return 0;
}
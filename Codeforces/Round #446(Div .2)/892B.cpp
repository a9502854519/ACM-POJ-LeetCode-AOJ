#include<iostream>
#include<cstdio>
#define MAX_N 1000000

using namespace std;

int n;
int L[MAX_N];

void solve(){
	int res = 0;
	int a = n, b = n; //[a, b)
	for(int i = n - 1; i >= 0; i--){
	//	printf(" i = %d  [%2d, %2d)\n",i, a, b);
		if(i < a){
			res++;
			b = i;
			a = i;
		}
		if(i - L[i] < a) a = i - L[i];
	}
	printf("%d\n", res);
}
int main(){
	cin>>n;
	for(int i = 0; i < n; i++){
		scanf("%d", L + i);
	}
	solve();
	return 0;
}
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_N 65536
using namespace std;

int p;
int euler[MAX_N+1];
void euler_phi(){
	for(int i = 0; i <= MAX_N; i++) euler[i] = i;
	for(int i = 2; i <= MAX_N; i++){
		if(euler[i] == i){
			for(int j = i; j <= MAX_N; j += i) euler[j] = euler[j] / i * (i-1);
		}
	}
}
int main(){
	euler_phi();
	while(scanf("%d", &p) != EOF){
		printf("%d\n", euler[p-1]);
	}
	return 0;
}
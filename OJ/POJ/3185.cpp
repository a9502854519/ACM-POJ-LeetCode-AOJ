#include<iostream>
#include<cstdio>
#include<algorithm>
#define INF 31
using namespace std;

int bowls[21];
int solve(){
	int f[21];
	fill(f, f+21, 0);
	int count[2];
	for(int k = 0; k < 2; k++){
		f[1] = k;
		count[k] = k;
		for(int i = 2; i <= 20; i++){
			f[i] = ((f[i-1] + f[i-2]) % 2) ^ bowls[i-1];
			if(f[i]) count[k] ++;
		}
		if((((f[19]+f[20]) % 2) ^ bowls[20]) == 1){
			count[k] = INF;
		}
	}
	return min(count[0], count[1]);
}
int main(){
	for(int i = 1; i <= 20; i++) scanf("%d", &bowls[i]);
	printf("%d\n", solve());
	return 0;
}
	
		
	
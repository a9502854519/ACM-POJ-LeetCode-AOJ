#include<iostream>
#include<cstdio>
#define MAX_N 100

using namespace std;

char str[MAX_N + 10];
char v[] = {'Q', 'A', 'Q'};

int find(int i, int k){
	if(k == 3) return 1;
	if(str[i] == '\0') return 0;
	
	int res = 0;
	for(; str[i] != '\0'; i++){
		if(str[i] == v[k]){
			res += find(i + 1, k + 1);
		}
	}
	return res;
}
int solve(){
	return find(0, 0);
}
int main(){
	scanf("%s\n", str);
	printf("%d\n", solve());
	return 0;
}
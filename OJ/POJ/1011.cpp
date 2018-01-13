#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX_N 64

using namespace std;

int ct[51];
int N, mx, sum;

bool dfs(int length, int limit, int s, int count){
	if(count == 0) return true;
	if(length == limit) length = 0;

	ct[s]--;
	if(length == 0){
		int tmp = mx;
		while(ct[tmp] == 0) tmp--;
		if(dfs(tmp, limit, tmp, count - 1)) return true;
	}else{
		for(int i = min(s, limit - length); i > 0; i--){
			if(ct[i] > 0 && dfs(length + i, limit, i, count)) return true;
		}
	}
	ct[s]++;

	return false;
}
int solve(){
	for(int i = mx; i <= sum; i++){
		if(sum % i == 0){
			if(dfs(0, i, mx, sum / i)) return i;
			printf("-----\n");
		}
	}
}
int main(){
	while(cin>>N && N != 0){
		mx = sum = 0;
		memset(ct, 0, sizeof(ct));
		for(int i = 0; i < N; i++){
			int s;
			scanf("%d ", &s);
			ct[s]++;
			mx = max(mx, s);
			sum += s;
		}
		printf("%d\n", solve());
	}
	return 0;
}
	
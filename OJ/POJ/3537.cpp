#include<iostream>
#include<cstdio>
#include<set>
#include<cstring>
#define MAX_N 2000

using namespace std;

int n;
int grundy[MAX_N+1];
int count [MAX_N+1];

void solve(){
	grundy[0] = 0;
	for(int j = 1; j <= n; j++){
		memset(count, 0, sizeof(count));
		for(int i = 1; i <= j; i++){
			int x1 = 0, x2 = 0;

			if(i > 3)     x1 = grundy[i-3];
			if(i < j - 2) x2 = grundy[j-i-2];
			count[x1^x2]++;
		}
		for(int g = 0; g <= n; g++){
			if(count[g] == 0){
			       	grundy[j] = g;
				break;
			}
		}
	}
	printf("%d\n", grundy[n] == 0 ? 2 : 1);
}
int main(){
	cin>>n;
	solve();
	return 0;
}

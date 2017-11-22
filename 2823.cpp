#include<iostream>
#include<cstdio>
#define MAX_N 1000000

using namespace std;

int n, k;
int a[MAX_N];
int deq[MAX_N];

void solve(){
	int s = 0, t = 0;
	for(int i = 0; i < n; i++){
		while(t > s && a[deq[t - 1]] >= a[i]) t--;
		deq[t++] = i;
		
		if(i - k + 1 >= 0){
			printf("%d ", a[deq[s]]);
		}
		if(deq[s] == i - k + 1){
			s++;
		}
	}
	printf("\n");

	s = 0, t = 0;
	for(int i = 0; i < n; i++){
		while(t > s && a[deq[t - 1]] <= a[i]) t--;
		deq[t++] = i;

		if(i - k + 1 >= 0){
			printf("%d ", a[deq[s]]);
		}
		if(deq[s] == i - k + 1){
			s++;
		}
	}
	printf("\n");
}
int main(){
	scanf("%d %d\n", &n, &k);
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
	}
	solve();
	return 0;
}

	

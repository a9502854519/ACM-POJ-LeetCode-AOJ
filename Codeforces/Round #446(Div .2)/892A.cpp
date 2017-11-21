#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 100000

using namespace std;
typedef long long ll;

int n, a[MAX_N], b[MAX_N];
ll V;

bool solve(){
	sort(b, b + n);
	return b[n - 1] + b[n - 2] >= V;
}
int main(){
	V = 0;
	cin>>n;
	for(int i = 0; i < n; i++){
		scanf("%d", a + i);
		V += (ll)a[i];
	}
	for(int i = 0; i < n; i++){
		scanf("%d", b + i);
	}
	printf("%s\n", solve() ? "YES" : "NO");
	return 0;
}
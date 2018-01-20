#include<iostream>
#include<cstdio>
#define MAX_N 1000

using namespace std;

int n;
int a[MAX_N];

int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a % b);
}
void solve(){
	for(int i = 1; i < n; i++){
		if(gcd(a[0], a[i]) != a[0]){
			cout << "-1\n";
			return;
		}
	}
	cout << 2 * n << endl;
	for(int i = 0; i < n; i++){
		printf("%d %d ", a[0], a[i]);
	}
	cout << endl;
}
int main(){
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	solve();
	return 0;
}

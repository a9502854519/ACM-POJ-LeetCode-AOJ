#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 22

using namespace std;

int n;
int a[MAX_N];
int b[MAX_N];

void solve(){
	sort(b, b + n);
	for(int i = 1; i < n; i++){
		if(b[i] == b[i - 1]){
			cout <<"-1\n";
			return;
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(a[i] == b[j]){
				if(j == 0){
				       	cout << b[n - 1] << " ";
				}else{
				       	cout << b[j - 1] << " ";
				}
			}
		}
	}
	cout << endl;
}
int main(){
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		b[i] = a[i];
	}
	solve();

	return 0;
}

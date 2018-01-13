#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;
typedef long long ll;

int n, m, k;

ll** mul(int b_size, ll **A, ll **B){
	ll** C;
	C = new ll*[n+1];
	for(int i = 0; i < n+1; i++){
		C[i] = new ll[b_size];
		fill(C[i], C[i] + b_size, 0);
		for(int k = 0; k < n+1; k++){
			if(A[i][k] > 0){
				for(int j = 0; j < b_size; j++){
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
	}
	return C;
}
		
ll** pow(ll** A, int m){
	ll** B = new ll*[n+1];
	for(int i = 0; i <= n; i++){
		B[i] = new ll[n+1];
		fill(B[i], B[i]+n+1, 0);
		B[i][i] = 1;
	}
	while(m > 0){
		if(m & 1) B = mul(n+1, A, B);
		A = mul(n+1, A, A);
		m >>= 1;
	}
	return B;
}
void solve(){
	ll** A = new ll* [n+1], **B = new ll* [n+1];
	
	
	for(int i = 0; i <= n; i++){
		A[i] = new ll[n+1];
		B[i] = new ll[1];
		B[i][0] = 0;
		fill(A[i], A[i]+n+1, 0);
		A[i][i] = 1;
	}
	
	B[n][0] = 1;
	while(k--){
		char ch;
		int i, j;
		scanf(" %c", &ch);
		if(ch == 'g'){
			scanf("%d", &i);
			A[i-1][n]++;
		}else if (ch == 's'){
			scanf("%d%d", &i, &j);
			swap(A[i-1], A[j-1]);
		}else{
			scanf("%d", &i);
			fill(A[i-1], A[i-1]+n+1, 0);
		}
	}
	
	A = pow(A, m);
	B = mul(1, A, B);
	for(int i = 0; i < n; i++){
		printf("%lld ", B[i][0]);
	}
	cout<<endl;
	delete A; delete B;
}
int main(){
	
	while(scanf("%d%d%d", &n, &m, &k)){
		if(n == 0 && m == 0 && k == 0) break;
		solve();
	}
				
	return 0;
}
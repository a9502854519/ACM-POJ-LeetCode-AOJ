#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int bit[101], n;
int data[101];
int dp[101][101];
int sum(int i){
	int s = 0;
	while(i>0){
		s+=bit[i];
		i -= i & -i;
	}
	return s;
}
int sum(int i, int j){
	return sum(j) - sum(i-1);
}
void add(int i, int x){
	while(i <= n){
		bit[i]+=x;
		i += i & -i;
	}
}
int main(){
	int j,m;
	while(cin>>n){
		if(n == 0) break;
		fill(bit, bit+n+1,0);
		for(int i=1;i<=n;i++){
			cin>>data[i];
			add(i, data[i]);
		}
		for(int i=1;i<=n;i++){
			dp[i][i] = data[i];
		}
		
		for(int len=1;len<n;len++){
			for(int i=1;i+len<=n;i++){
				j = i+len;
				m = sum(i, j);
				for(int k = i; k < j; k++){
					m = max(m,sum(i,k) + sum(k+1,j) - dp[k+1][j]);
					m = max(m,sum(k+1, j) + sum(i,k) - dp[i][k]);
				}
				dp[i][j] = m;
			}
		}
		cout<<2*dp[1][n] - sum(1,n)<<endl;	
	}
	return 0;
}
		
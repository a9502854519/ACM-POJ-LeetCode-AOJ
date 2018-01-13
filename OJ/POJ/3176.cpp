#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 350

using namespace std;

int dp[MAX_N][MAX_N];

int  main(){
	int N;
	cin>>N;
			
	for(int i = 0; i < N; i++){
		for(int j = 0; j <= i; j++){
			scanf("%d", &dp[i][j]);
			int temp = 0;
			if(i > 0){
				if(j < i) temp = max(temp, dp[i-1][j]);
				if(j > 0) temp = max(temp, dp[i-1][j-1]);
			}
			dp[i][j] += temp;
		}
	}
	int res = 0;
	for(int i = 0; i < N; i++){
		res = max(res, dp[N-1][i]);
	}
	cout<<res<<endl;	
	return 0;
}


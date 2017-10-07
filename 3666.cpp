#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define MAX_N 2000
#define INF 1E9
using namespace std;

int N;
int dp_increase[MAX_N];
int dp_decrease[MAX_N];
int A[MAX_N];
vector<int> B;

void solve(){
	sort(B.begin(), B.end());
	B.erase(unique(B.begin(), B.end()), B.end());
	memset(dp_increase, 0, sizeof(dp_increase));
	memset(dp_decrease, 0, sizeof(dp_decrease));
	
	for(int i = 0; i < N; i++){
		for(int j = 0, k = B.size()-1; j < B.size(), k >= 0; j++, k--){
			dp_increase[j] += abs(A[i] - B[j]);
			dp_decrease[k] += abs(A[i] - B[k]);
			if(j > 0){
				dp_increase[j] = min(dp_increase[j], dp_increase[j-1] - abs(A[i] - B[j-1]) + abs(A[i] - B[j]));
			}
			if(k < B.size()-1){
				dp_decrease[k] = min(dp_decrease[k], dp_decrease[k+1] - abs(A[i] - B[k+1]) + abs(A[i] - B[k]));
			}
			
		}
	}
	int res = INF;
	for(int j = 0; j < B.size(); j++){
		res = min(res, dp_increase[j]);
		res = min(res, dp_decrease[B.size()-1-j]);
	}
	printf("%d\n", res);
}
int main(){
	cin>>N;
	for(int i = 0; i < N; i++){
		scanf("%d", A+i);
		B.push_back(A[i]);
	}
	solve();
	return 0;
}
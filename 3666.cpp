/* 成本的關係，若一個點要調整高度
 * ，那它一定得調整到跟某個點一樣
 * 高，因此得把高度離散化。
 * 再來考慮遞增減的問題，這個不礙
 * 事，開兩個陣列就好。
 *
 * 遞增情況：
 * dp[i][j] --> 第i個點，調整成第j個高度B(j)時的最小成本
 * dp[i][j] = min(dp[i - 1][j - k]) + | A(i) - B(j) | , 0 <= k <= j
 * 
 * 遞減情況：
 * dp[i][j] = min(dp[i - 1][j + k]) + | A(i) - B[j] | , 0 <= k <= max_height
 * 
 * P.S. 這題的數據沒有遞減的情況，
 * 所以網路上很多題解都是錯的。大
 * 概是有個思慮不周的北七寫出來的，
 * 然後有更多北七把它抄到自己的博
 * 客，假裝是自己寫的。一傳十十傳
 * 百。總之別信就對了。
 */
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
	B.erase(unique(B.begin(), B.end()), B.end()); //離散化
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
	i	res = min(res, dp_decrease[B.size()-1-j]);
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

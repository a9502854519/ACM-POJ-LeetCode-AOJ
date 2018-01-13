/* 這題有三個參數要考慮：時間、走了多少步、以及目前在哪棵樹下。
 * 因為這題只有兩棵樹，所以可以從走的步數，判斷目前到底在哪裡。
 * 所以參數只剩兩個，考慮在i分鐘，走了j步後，能吃到的最多蘋果數
 * 如果在第i分鐘時保持不動，狀態就會轉移到第i-1分，走了j步後
 * 巴拉巴拉....；同理可推，若第i分鐘時，從另外一棵樹走了過來，
 * 則狀態便轉移到第i-1分鐘，走了j-1步後巴拉巴拉....。
 * 
 * dp[i][j] : 第i分鐘，走了j步時，能吃到的最多蘋果數量
 * dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]) + !(Tree[i]^(j&1))
 */

#include<iostream>
#include<algorithm>
#include<cstring>
#define MAX_W 30
#define MAX_T 1000

using namespace std;

int dp[MAX_W+1];
int Tree[MAX_T];
int T, W;

void solve(){
	memset(dp, 0, sizeof(dp));
	dp[0] = 1 - Tree[0];  
	dp[1] = Tree[0];     

	for(int i = 1; i < T; i++){
		dp[0] = dp[0] + (1 - Tree[i]);
		for(int j = W; j >= 1; j--){
			dp[j] = max(dp[j], dp[j-1]) + !(Tree[i] ^ (j & 1));
			 //j & 1相當於j % 2，可以判斷j的奇偶性-->即可判斷
			 //在哪棵樹下。
			 //這裡會有四種情況：蘋果在第0 or 1棵樹，牛在第0 or 1
			 //棵樹下，可以寫出下列真值表：
			 //  蘋果   牛  結果(1代表有吃到，0則否)
			 //   0      0       1
			 //   0      1       0
			 //   1      0       0
			 //   1      1       1
			 //可以發現，結果是前兩個數字XOR後再取反
		}
	}	
	
	int res = 0;
	for(int i = 0; i <= W; i++) res = max(res, dp[i]);
	
	cout<<res<<endl;
}
int main(){
	cin>>T>>W;
	for(int i = 0; i < T; i++){
		cin>>Tree[i];
		Tree[i]--;
	}
	solve();
	return 0;
}	
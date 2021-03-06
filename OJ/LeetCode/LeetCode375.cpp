/* 只有兩個數字的情況，假設1, 2。
 * 很明顯地，最好的猜法是猜1，然
 * 後付出$1，最後知道答案是2。
 * 再來看看三個數字的情況，1, 2, 3。
 * 如果猜1，那剩下2, 3，這時得猜2，
 * 遊戲結束，付出$1+$2 = 3。
 * 如果猜2，那不管答案是比較大或小，
 * 我們都可以馬上知道答案，成本為$2
 * 猜3的話，下一個得猜1，付出$1+$3 = 4
 * 因此最好的猜法是2，成本為$2
 * 再來看看4個數字的情況，1, 2, 3, 4
 * 如果我們猜1，剩下2, 3, 4，根據剛剛
 * 的計算結果，這2, 3, 4的最差情況
 * 會花費$3，因此成本為$1+$3 = 4
 * 猜2，會分成兩部份：1和3, 4。1的部
 * 份不用再猜任何數字，3, 4的話，
 * 根據剛剛的計算結果，最差情況為
 * $3，成本為$2+$3 = 5。3和4同理。
 * 根據上述的推理結果，可以寫出以
 * 下遞推式：
 * dp[i][j] --> 區間[i, j]的最小猜數字成本
 * dp[i][j] = min(k + max(dp[i][k-1], dp[k+1][j]))  i < k < j
 */
class Solution{
	public:
		int sum;
		int getMoneyAmount(int n){
			//initialize
			int dp[n+1][n+1];
			for(int i=1; i<n; i++){
				dp[i][i] = 0;
				dp[i][i+1] = i;
			}
			dp[n][n] = 0;
			
			for(int L = 2; L < n; L++){
				for(int i = 1; (i+L) <= n; i++){
					int j = i + L;
					dp[i][j] = 10000000000;
					for(int k = i+1; k < i+L; k++){
						sum = k + max(dp[i][k-1] , dp[k+1][j]);
						dp[i][j] = min(dp[i][j], sum);
					}
				}
			}
			return dp[1][n];
		}
};
/*背包問題題題題題題題題題題題題*/
class Solution {
	public:
        bool canPartition(vector<int>& nums) {
            int size = nums.size();
            int sum = 0;
            for(int i=0; i<size; i++) sum+=nums[i];
                if(sum%2 == 1) return false; //奇收不ok

                int dp[(sum/2)+1][size+1];
                //dp(i, j) : 前j個數字組成i是否可行
                //這裡我不知道哪根筋不對，寫反了
                for(int i=0; i<=sum/2; i++){
                    for(int j=0; j<=size; j++){
                        if(!i) dp[i][j] = 1;　//dp(0, j) = true
                        else   dp[i][j] = 0;
                    }
                }
                for(int i=1; i<=sum/2; i++){
                    for(int j=1; j<=size; j++){
						if(i>=nums[j-1])
							dp[i][j] = dp[i][j-1] | dp[i-nums[j-1]][j-1];
                    }
                }
                return (dp[sum/2][size] ? true : false);
        }
};

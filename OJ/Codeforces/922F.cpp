#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_N 300000 + 100

using namespace std;
typedef long long ll;

int n, k;
ll dp[MAX_N];
bool is_prime[MAX_N];

void solve(){
    memset(dp, 0, sizeof(dp));
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for(int i = 1; i <= n; i++){
        for(int j = i * 2; j <= n; j += i){
            dp[j]++;
            is_prime[j] = i == 1;
        }
        dp[i] += dp[i - 1];
    }
    
    vector<int> res;
    if(dp[n] >= k){
        n = lower_bound(dp, dp + n + 1, k) - dp;
        k = dp[n] - k;
        for(int i = 1; i <= n; i++){
            if(!is_prime[i]) res.push_back(i);
            else{
                int d = n / i;
                if(d <= k){
                    k -= d;
                }else{
                    res.push_back(i);
                }
            }
        }
    }
    if(k > 0){
        cout << "No\n";
        return;
    }
    printf("Yes\n%d\n", res.size());
    for(int i = 0; i < res.size(); i++) cout << res[i] << " ";
    cout << endl;
}
int main(){
    cin >> n >> k;
    solve();
    return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX_N 5000 + 100
#define MAX_K 5000 + 100

using namespace std;

int N, K, V;
bool dp[MAX_N][MAX_K];
int v[MAX_N];
bool s[MAX_N][MAX_K];

void solve(){
    dp[0][0] = true;
    bool ok = false;
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= K; j++){
            if(dp[i][j]){
                dp[i + 1][j] = dp[i + 1][(j + v[i]) % K] = s[i + 1][(j + v[i]) % K] = true;
            }
            ok |= s[i + 1][V % K];
        }
    }
    if(!dp[N][V % K]) cout << "NO\n";
    else{
        cout << "YES\n";
        vector<int> ps, qs;
        int tmp = V % K;
        for(int i = N - 1; i >= 0; i--){
            if(s[i + 1][tmp]){
                ps.push_back(i + 1);
                tmp = ((tmp - v[i]) % K + K) % K;
            }else{
                qs.push_back(i + 1);
            }
        }
        int des = -1, total = 0;
        if(ps.size() > 0){
            des = ps.back(), total = v[ps.back() - 1];
            for(int i = 0; i < ps.size() - 1; i++){
                int k = ps[i];
                if(v[k - 1] > 0){
                    printf("%d %d %d\n", v[k - 1] / K + (v[k - 1] % K > 0), k, des);
                    total += v[k - 1];
                }
            }
        }
        if(total <= V && qs.size() > 0){
            int des2 = qs.back();
            for(int i = 0; i < qs.size() - 1; i++){
                int k = qs[i];
                if(v[k - 1] > 0){
                    printf("%d %d %d\n", v[k - 1] / K + (v[k - 1] % K > 0), k, des2);
                }
            }
            if(des == -1) des = des2 > 1 ? des2 - 1 : des2 + 1;
            if(V > total) printf("%d %d %d\n", (V - total) / K, des2, des);
        }else if(total > V){
            printf("%d %d %d\n", (total - V) / K, des, (des > 1 ? des - 1 : des + 1));
        }
    }
}
int main(){
    cin >> N >> K >> V;
    int tmp = 0;
    for(int i = 0; i < N; i++){
        scanf("%d", v + i);
        tmp += v[i];
    }
    if(tmp >= V) solve();
    else cout << "NO\n";
    
    return 0;
}
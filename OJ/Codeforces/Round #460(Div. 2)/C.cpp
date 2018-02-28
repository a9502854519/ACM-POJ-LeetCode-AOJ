#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 2000 + 10

using namespace std;

int n, m, k;
char seat[MAX_N][MAX_N];
int ct[2][MAX_N][MAX_N];

int solve(){
    // for(int i = 0; i < n; i++){
        // for(int j = 0; j < m; j++){
            // cout << seat[i][j];
        // }
        // cout << endl;
    // }
    memset(ct, 0, sizeof(ct));
    int res = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(seat[i][j] == '.'){
                ct[0][i][j] = ct[1][i][j] = 1;
                if(j > 0) ct[0][i][j] += ct[0][i][j - 1];
                if(i > 0) ct[1][i][j] += ct[1][i - 1][j];
                res += (ct[0][i][j] >= k) + (ct[1][i][j] >= k) - (k == 1);
            }
        }
    }
    return res;
}
int main(){
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++){
        scanf("%s\n", seat[i]);
    }
    cout << solve() << endl;
    return 0;
}
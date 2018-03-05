#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_K 200 + 10

using namespace std;

int n, k;
int w[MAX_K];

int solve(){
    int res = 0;
    for(int i = 0; i < k - 1; i++){
        int tmp = w[i + 1] - w[i] + 1;
        res = max(res, tmp / 2 + (tmp & 1));
    }
    res = max(res, max(w[0], n + 1 - w[k - 1]));
    return res;
}
int main(){
    int T;
    cin >> T;
    w[0] = 0;
    for(int c = 1; c <= T; c++){
        cin >> n >> k;
        for(int i = 0; i < k; i++) cin >> w[i];
        cout << solve() << endl;
    }
    return 0;
}
#include<iostream>
#include<cstdio>
#define MAX_N 100000 + 100

using namespace std;
typedef long long ll;

ll n, m[MAX_N], s[MAX_N];
ll solve(){
    ll k = 1, res = 0;
    for(int i = n - 1; i >= 0; i--){
        k = max(k, m[i] + 1);
        s[i] = k--;
    }
    k = 1;
    for(int i = 0; i < n; i++){
        k = max(k, s[i]);
        res += k - m[i] - 1;
    }
    return res;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%I64d", m + i);
    cout << solve() << endl;
    return 0;
}
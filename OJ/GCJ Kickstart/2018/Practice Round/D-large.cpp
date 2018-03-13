#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 200000 + 100

using namespace std;
typedef long long ll;

int n, q;
ll a[MAX_N], s[MAX_N];

ll check(ll x){
    ll res = 0;
    for(int i = 1; i <= n; i++){
         res += upper_bound(a + i, a + n + 1, x + a[i - 1]) - (a + i);
    }
    return res;
}
ll get(ll v){
    ll lb = 0, ub = a[n], mid;
    while(ub - lb > 1){
        mid = (ub + lb) / 2;
        if(check(mid) >= v) ub = mid;
        else lb = mid;
    }
    return ub;
}
ll calc(ll v, ll p){
    ll res = 0, cnt = 0;
    // printf("v = %lld  rank = %lld\n", v, p);
    for(int i = 1; i <= n; i++){
        int j = upper_bound(a + i, a + n + 1, v + a[i - 1]) - a;
        // printf("[%d, %d)  %lld\n", i, j, s[j - 1] - s[i - 1] - a[i - 1] * (j - i));
        res += s[j - 1] - s[i - 1] - a[i - 1] * (j - i);
        
        cnt += j - i;
    }
    // printf("res = %lld  cnt = %lld\n", res, cnt);
    return res - (cnt - p) * v;
}
void solve(){
    cin >> n >> q;
    a[0] = s[0] = 0;
    for(int i = 1; i <= n; i++){
        scanf("%d", a + i);
        a[i] += a[i - 1];
        s[i] = s[i - 1] + a[i];
    }
    // for(int i = 1; i <= n; i++) printf("%2lld ", a[i]);
    // cout << endl;
    // for(int i = 1; i <= n; i++) printf("%2lld ", s[i]);
    // cout << endl;
    
    ll L, R;
    ll A, B;
    while(q--){
        scanf("%lld %lld\n", &L, &R);
        A = get(L), B = get(R);
        // printf("%lld %lld\n", A, B);
        cout << calc(B, R) - calc(A, L - 1) << endl;
    }
}
int main(){
    int T;
    cin >> T;
    for(int kase = 1; kase <= T; kase++){
        printf("Case #%d:\n", kase);
        solve();
    }
    return 0;
}
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#define MAX_N 100000 + 10

using namespace std;
typedef long long ll;

ll n, x, k;
ll a[MAX_N];

void calc(ll& lb, ll& ub, ll v){
    lb = (v / x - k) * x + 1;
    ub = (v / x - k + 1) * x;
    if(ub > v) ub = v;
}
ll solve(){
    sort(a, a + n);
    ll lb, ub, res = 0;
    for(int i = 0; i < n; i++){
        calc(lb, ub, a[i]);
        // printf("%d %d\n", lb, ub);
        ll tmp = upper_bound(a, a + n, ub) - lower_bound(a, a + n, lb);
        if(tmp > 0) res += tmp;
    }
    return res;
}
int main(){
    cin >> n >> x >> k;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    cout << solve() << endl;
    return 0;
}
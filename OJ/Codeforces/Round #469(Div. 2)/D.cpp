#include<iostream>
#include<cstdio>

using namespace std;
typedef long long ll;

ll n, m;
int q;

ll calc(ll l, ll r){
    return (r - l) / 2 + ((r - l) & 1) * (l & 1);
}
ll solve(){
    m--;
    ll gap = 0, nxt = n, tmp;
    while((m + gap) & 1){
        m >>= 1;
        tmp = nxt;
        nxt = calc(gap, gap + nxt);
        gap += tmp;
    }
    return (m + gap) / 2 + 1;
}
int main(){
    cin >> n >> q;
    while(q--){
        cin >> m;
        cout << solve() << endl;
    }
    return 0;
}
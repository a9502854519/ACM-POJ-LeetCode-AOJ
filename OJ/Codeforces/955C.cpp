#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
#define MAX_P 60

using namespace std;
typedef long long ll;

ll L, R;
vector<ll> s;

bool square(ll x){
    ll t = sqrt(x);
    return t * t == x;
}
void init(){
    for(ll i = 2; i <= 1e6; i++){
        if(!square(i)){
            double tmp = i * i;
            for(ll j = i * i, t = 2; tmp <= 1e18; j *= i, t++, tmp *= i){
                if(t & 1){
                    s.push_back(j);
                }
            }
        }
    }
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
}
ll solve(ll x){
    ll ub = sqrt(x) + 1, lb = 0, mid;
    while(ub - lb > 1){
        mid = (ub + lb) / 2;
        if(mid * mid <= x) lb = mid;
        else ub = mid;
    }
    int k = upper_bound(s.begin(), s.end(), x) - s.begin();
    return k + lb;
}
int main(){
    init();
    int Q;
    cin >> Q;
    
    while(Q--){
        scanf("%I64d %I64d\n", &L, &R);
        printf("%I64d\n", solve(R) - solve(L - 1));
    }
    return 0;
}
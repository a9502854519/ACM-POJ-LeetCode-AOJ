#include<iostream>
#include<cstdio>

using namespace std;
typedef long long ll;

ll a, b, p, x;

ll pow(ll a, ll b, ll n){
    ll A = a, B = 1;
    while(b > 0){
        if(b & 1) B = B * A % n;
        A = A * A % n;
        b >>= 1;
    }
    return B;
}
ll solve(){
    ll res = 0;
    ll new_p = p * (p - 1);
    for(ll j = 0; j < p - 1; j++){
        ll i = pow(a, j * (p - 2), p) * b % new_p; 
        ll tmp = (i * (p - 1) % new_p * (p - 1) % new_p + j * p % new_p) % new_p;
        if(tmp <= x) res += 1 + (x - tmp) / new_p;
    }
    return res;
}
int main(){
    cin >> a >> b >> p >> x;
    cout << solve() << endl;
    return 0;
}
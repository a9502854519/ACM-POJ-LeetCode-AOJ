#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#define MAX_N 1000 + 10

using namespace std;
typedef long long ll;

const ll MOD = 1000003;
ll n, k, L[MAX_N + 1], L1[MAX_N + 1], L2[MAX_N + 1];
bool is_prime[MAX_N];
vector<ll> divs;
vector<ll> factor;

void init(){
    L1[1] = 2, L2[1] = 0, L[1] = 2;
    for(int i = 2; i <= k && i <= n; i++){
        L1[i] = (L1[i - 1] + L2[i - 1]) % MOD;
        L2[i] = (L1[i - 1] + L2[i - 1]) % MOD;
        L[i] = L1[i] + L2[i];
    }
    ll t1 = 2, t2 = 0;
    for(int i = k + 1; i <= n; i++){
        if(i - k - 1 > 0){
            t1 = L2[i - k - 1];
            t2 = L1[i - k - 1];
        }
        L1[i] = (L1[i - 1] + L2[i - 1] - t1) % MOD;
        L2[i] = (L1[i - 1] + L2[i - 1] - t2) % MOD;
        L[i] = L1[i] + L2[i];
    }
    //prime
    fill(is_prime, is_prime + 32, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i * i <= n; i++){
        if(is_prime[i]){
            for(int j = i * 2; j <= n; j += i){
                is_prime[j] = false;
            }
        }
    }
}
void factorize(){
    factor.clear();
    int m = n;
    for(int i = 1; i * i <= n; i++){
        if(is_prime[i] && m % i == 0){
            factor.push_back(i);
            while(m % i == 0) m /= i;
        }
    }
    if(m != 1) factor.push_back(m);
}
void divisor(){
    divs.clear();
    for(int i = 1; i <= n; i++){
        if(n % i == 0) divs.push_back(i);
    }
}
ll mod_pow(ll a, ll b){
    //a ^ b;
    ll A = a, B = 1;
    while(b > 0){
        if(b & 1) B = B * A % MOD;
        A = A * A % MOD;
        b >>= 1;
    }
    return B;
}
ll calc(int m){
    ll res = L[m];
    if(m <= k && k < n) res -= 2;
    else if(m > k + 1){
        for(int i = 2 * k; i > k; i--){
            if(m >= i + 1){
                res = (res - L1[m - i] * (2 * k - i + 1) % MOD) % MOD;
            }
        }
    }
    return (res + MOD) % MOD;
}
ll solve(){
    init();
    factorize();
    divisor();
    //polya
    ll res = 0;
    for(int i = 0; i < divs.size(); i++){
        ll euler = n / divs[i];
        for(int j = 0; j < factor.size(); j++){
            if((n / divs[i]) % factor[j] == 0) euler = euler / factor[j] * (factor[j] - 1);
        }
        res += calc(divs[i]) * euler % MOD;;
    }
    return res * mod_pow(n, MOD - 2) % MOD;
}
int main(){
    while(~scanf("%d %d\n", &n, &k) && (n || k)){
        cout << solve() << endl;
    }
    return 0;
}
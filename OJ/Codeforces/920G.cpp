#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_P 1000 + 10

using namespace std;
typedef long long ll;

int x, p, k, base;
bool is_prime[MAX_P];
vector<int> prime;
vector<int> fac;
vector<int> ps;

void calc_prime(){
    fill(is_prime, is_prime + MAX_P , true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= MAX_P; i++){
        if(is_prime[i]){
            prime.push_back(i);
            for(int j = i * 2; j <= MAX_P; j += i){
                is_prime[j] = false;
            }
        }
    }
}
void factorize(){
    fac.clear();
    for(int i = 0; i < prime.size() && prime[i] * prime[i] <= p; i++){
        if(p % prime[i] == 0){
            fac.push_back(prime[i]);
            while(p % prime[i] == 0) p /= prime[i];
        }
    }
    if(p != 1) fac.push_back(p);
}
void inc_exc(){
    ps.clear();
    int n = fac.size();
    for(int i = 1; i < (1 << n); i++){
        int div = 1, cnt = 0;
        for(int j = 0; j < n; j++){
            if((i >> j) & 1){
                div *= fac[j];
                cnt++;
            }
        }
        ps.push_back(div * (cnt % 2 == 1 ? 1 : -1));
    }
}
ll calc(ll v){
    ll res = 0;
    for(int i = 0; i < ps.size(); i++){
        res += (v / ps[i]);
    }
    return v - res;
}
int get_ub(){
    for(int t = 0;; t++){
        ll tmp = x + (1 << t);
        if(calc(tmp) - base >= k) return t;
    }
}
ll solve(){
    factorize();
    inc_exc();
    base = calc(x);
    
    int t = get_ub();
    ll ub = x + (1 << t), lb = x + (1 << (t - 1)), mid;
    // printf("%I64d %I64d\n", ub, lb);
    while(ub - lb > 1){
        mid = (ub + lb) / 2;
        if(calc(mid) - base >= k) ub = mid;
        else lb = mid;
    }
    return ub;
}
int main(){
    calc_prime();
    int T;
    cin >> T;
    while(T--){
        scanf("%d %d %d\n", &x, &p, &k);
        printf("%I64d\n", solve());
    }
    return 0;
}
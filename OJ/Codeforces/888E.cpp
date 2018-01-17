#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 35 + 10

using namespace std;
typedef long long ll;

ll n, m;
ll a[MAX_N];
ll b[1 << 18];

int bs(ll v){
   int ub = 1 << (n / 2), lb = 0, mid;
   while(ub - lb > 1){
       mid = (ub + lb) / 2;
       if(b[mid] <= v) lb = mid;
       else ub = mid;
   }
   return lb;
}
ll solve(){
    int k = n / 2;
    for(int i = 0; i < (1 << k); i++){
        ll sum = 0;
        for(int j = 0; j < k; j++){
            if((i >> j) & 1) sum = (sum + a[j]) % m;
        }
        b[i] = sum;
    }
    sort(b, b + (1 << k));
    ll res = 0;
    for(int i = 0; i < (1 << (n - k)); i++){
        ll sum = 0;
        for(int j = 0; j < n - k; j++){
            if((i >> j) & 1) sum = (sum + a[j + k]) % m;
        }
        int tmp = bs(m - sum - 1);
        res = max(res, (sum + b[tmp]) % m);
    }
    return res;
}
int main(){
    cin >> n >> m;
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    cout << solve() << endl;
    return 0;
}
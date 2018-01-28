#include<iostream>
#include<vector>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define MAX_Y 1000000 + 50
#define MAX_P 1000 + 50

using namespace std;
typedef long long ll;

int x, y;
ll exp_2[MAX_Y + 1]; //2 ^ i % MOD
vector<int> fac;
bool prime[MAX_P + 1];
ll C[MAX_Y + 1][20];
const ll MOD = 1000000007;

void init(){
    //2 ^ i % MOD
    ll n = 1;
    for(int i = 0; i <= MAX_Y; i++){
        exp_2[i] = n;
        n = n * 2 % MOD;
    }
    // prime
    fill(prime, prime + MAX_P + 1, true);
    prime[0] = prime[1] = false;
    for(int i = 2; i <= MAX_P; i++){
        if(prime[i]){
            for(int j = i * 2; j <= MAX_P; j += i){
                prime[j] = false;
            }
        }
    }
    // combinatoric
    
    C[0][0] = 1;
    for(int i = 1; i <= MAX_Y; i++){
        for(int j = 0; j <= i && j < 20; j++){
            C[i][j] = 0;
            if(j < i) C[i][j] = (C[i][j] + C[i - 1][j]) % MOD;
            if(j > 0) C[i][j] = (C[i][j] + C[i - 1][j - 1]) % MOD;
        }
    }
    
}
void factorize(){
    fac.clear();
    int n = x;
    for(int i = 2; i * i <= x; i++){
        if(prime[i] && n % i == 0){
            fac.push_back(0);
            while(n % i == 0){
                fac[fac.size() - 1]++;
                n /= i;
            }
        }
    }
    if(n != 1) fac.push_back(1);
}
ll comb(int n, int m){
    return C[n + m - 1][m];
}
int solve(){
    factorize();
    ll res = 1;
    for(int i = 0; i < fac.size(); i++){
        res = (res * comb(y, fac[i])) % MOD;
    }
    return (res * exp_2[y - 1]) % MOD;
}
int main(){
    init();
    int q;
    cin >> q;
    while(q--){
        scanf("%d %d\n", &x, &y);
        printf("%d\n", solve());
    }
    return 0;
}

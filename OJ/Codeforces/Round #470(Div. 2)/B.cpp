#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define MAX_P 1000 + 100
#define INF 1E9

using namespace std;

int X;
vector<int> prime;
bool is_prime[MAX_P];

void init(){
    fill(is_prime, is_prime + MAX_P, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < MAX_P; i++){
        if(is_prime[i]){
            prime.push_back(i);
            for(int j = i; j < MAX_P; j += i){
                is_prime[j] = false;
            }
        }
    }
}
int get(int x){
    int res = -1;
    for(int i = 0; prime[i] * prime[i] <= x && i < prime.size(); i++){
        if(x % prime[i] == 0){
            res = max(res, prime[i]);
            while(x % prime[i] == 0) x /= prime[i];
        }
    }
    if(x != 1){
        res = max(res, x);
    }
    return res;
}
int solve(){
    init();
    int p = get(X), res = X;
    for(int i = (X / p - 1) * p + 1; i <= X; i++){
        int x = get(i);
        if(i != x) res = min(res, (i / x - 1) * x + 1);
    }
    return res;
}
int main(){
    cin >> X;
    cout << solve() << endl;
    return 0;
}
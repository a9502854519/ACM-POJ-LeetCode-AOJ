//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永無BUG
//
//
//
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define MAX_N 100000 + 10
#define MAX_P 2000000 + 10

using namespace std;

bool is_prime[MAX_P];
bool used[MAX_P];
vector<int> prime;
int n, a[MAX_N];

void init(){
    fill(is_prime, is_prime + MAX_P, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < MAX_P; i++){
        if(is_prime[i]){
            prime.push_back(i);
            for(int j = i * 2; j < MAX_P; j += i){
                is_prime[j] = false;
            }
        }
    }
}
vector<int> factorize(int p){
    vector<int> res;
    for(int i = 0; i < prime.size() && prime[i] * prime[i] <= p; i++){
        if(p % prime[i] == 0){
            res.push_back(prime[i]);
            while(p % prime[i] == 0) p /= prime[i];
        }
    }
    if(p != 1) res.push_back(p);
    return res;
}
vector<int> get_next(int x){
    for(int i = x + 1;; i++){
        vector<int> fac = factorize(i);
        bool tmp = true;
        for(int j = 0; j < fac.size() && tmp; j++){
            tmp &= !used[fac[j]];
        }
        if(tmp){
            printf("%d ", i);
            return fac;
        }
    }
}
void solve(){
    int i;
    bool res = true;
    for(i = 0; i < n && res; i++){
        vector<int> fac = factorize(a[i]);
        for(int j = 0; j < fac.size() && res; j++) res &= !used[fac[j]];
        
        if(res){
            printf("%d ", a[i]);
        }else{
            fac = get_next(a[i]);
        }
        for(int j = 0; j < fac.size(); j++) used[fac[j]] = true;
    }
    int idx = 0;
    for(; i < n; i++){
        while(idx < prime.size() && used[prime[idx]]) idx++;
        if(idx < prime.size()){
            printf("%d ", prime[idx]);
            used[prime[idx]] = true;
        }
    }
}
int main(){
    init();
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    solve();
    return 0;
}

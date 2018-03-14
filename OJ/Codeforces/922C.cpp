#include<iostream>
#include<cstdio>
#include<unordered_map>

using namespace std;
typedef long long ll;

ll n, k;
unordered_map<int, bool> mp;

void solve(){
    bool res;
    for(ll i = 1; i <= k; i++){
        if(mp.find(n % i) == mp.end()) mp[n % i] = true;
        else{
            puts("No");
            return;
        }
    }
    puts("Yes");
}
int main(){
    cin >> n >> k;
    solve();
    return 0;
}
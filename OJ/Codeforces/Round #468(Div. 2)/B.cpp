#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int n, a, b;

void solve(){
    a--; b--;
    int res = 0;
    while(a != b){
        res++;
        a >>= 1; b >>= 1;
    }
    if((1 << res) >= n) cout << "Final!\n";
    else cout << res << endl;
}
int main(){
    cin >> n >> a >> b;
    solve();
    return 0;
}
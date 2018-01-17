#include<iostream>
#include<cstdio>
#define MAX_N 1000

using namespace std;
typedef long long ll;

int n, k;
ll D[5] = {1, 0, 1, 2, 9};

ll solve(){
    ll coff = 1, res = 0;
    for(int i = 0; i <= k; i++){
        res += coff * D[i];
        coff = (coff * (n - i)) / (i + 1);
    }
    return res;
}
int main(){
    cin >> n >> k;
    cout << solve() << endl;
    return 0;
}
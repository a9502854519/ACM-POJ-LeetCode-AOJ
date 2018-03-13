#include<iostream>
#include<cstdio>
#include<cmath>
#define INF 1E9

using namespace std;

int n, pos, l, r;

int solve(){
    if(r - l + 1 == n) return 0;
    int res = INF;
    if(r < n) res = min(res, abs(r - pos) + 1);
    if(l > 1) res = min(res, abs(pos - l) + 1);
    if(r < n && l > 1) res += r - l + 1;
    return res;
}
int main(){
    cin >> n >> pos >> l >> r;
    cout << solve() << endl;
    return 0;
}
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>

using namespace std;

int l, r, a;

int solve(){
    int tmp = abs(l - r);
    if(a < tmp) return (min(l, r) + a) * 2;
    else return max(l, r) * 2 + ((a - tmp) / 2 * 2);
}
int main(){
    cin >> l >> r >> a;
    cout << solve() << endl;
    return 0;
}
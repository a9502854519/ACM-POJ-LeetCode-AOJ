#include<iostream>
#include<cstdio>

using namespace std;
typedef long long ll;

void solve(ll a, ll b){
    if((a == 0 || b == 0) || (b / a < 2 && a / b < 2)){
        cout << a << " " << b << endl;
        return;
    }
    if(a > b) solve(a - a / (2 * b) * 2 * b, b);
    else solve(a, b - b / (2 * a) * 2 * a);
}
int main(){
    ll a, b;
    cin >> a >> b;
    solve(a, b);
    return 0;
}
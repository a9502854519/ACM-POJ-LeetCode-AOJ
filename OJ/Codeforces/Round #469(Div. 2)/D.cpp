#include<iostream>
#include<cstdio>

using namespace std;
typedef long long ll;

ll n, m;
int q;

ll solve(){
    while((m & 1) == 0){
        m += (n - m / 2);
    }
    return (m + 1) / 2;
}
int main(){
    cin >> n >> q;
    while(q--){
        cin >> m;
        cout << solve() << endl;
    }
    return 0;
}
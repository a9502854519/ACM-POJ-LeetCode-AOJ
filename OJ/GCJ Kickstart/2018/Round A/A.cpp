#include<iostream>
#include<cstdio>

using namespace std;
typedef long long ll;

string N;

void solve(){
    int i;
    ll res = 0, p = 0, m = 0;
    int tmp;
    for(i = 0; i < N.length(); i++){
        tmp = N[i] - '0';
        if(tmp % 2 == 1){
            p = 1;
            m = 0;
            for(int j = i + 1; j < N.length(); j++){
                res = res * 10 + N[j] - '0';
                m = m * 10 + 1;
                p *= 10;
            }
            break;
        }
    }
    p -= res;
    m += res + 1;
    if(tmp == 9 && (i == 0 || (N[i - 1] - '0') % 2 == 0)) cout << m << endl;
    else cout << min(p, m) << endl;
}
int main(){
    int T;
    cin >> T;
    for(int kase = 1; kase <= T; kase++){
        cin >> N;
        printf("Case #%d: ", kase);
        solve();
    }
    return 0;
}
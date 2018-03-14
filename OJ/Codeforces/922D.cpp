#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAX_N 100000 + 100

using namespace std;
typedef long long ll;

struct Data{
    ll s, h, t;
    Data(){
        s = h;
    }
    Data(ll s, ll h, ll t) : s(s), h(h), t(t) {}
}data[MAX_N];
int n;

bool cmp(Data &a, Data &b){
    return a.s * b.h > b.s * a.h;
}
ll solve(){
    ll res = 0, s = 0;
    sort(data, data + n, cmp);
    for(int i = 0; i < n; i++){
        res += data[i].t + data[i].h * s;
        s += data[i].s;
    }
    return res;
}
int main(){
    cin >> n;
    string S;
    for(int i = 0; i < n; i++){
        cin >> S;
        ll s = 0, h = 0, t = 0;
        for(int j = 0; j < S.length(); j++){
            if(S[j] == 's') s++;
            else{
                h++;
                t += s;
            }
        }
        data[i] = Data(s, h, t);
    }
    cout << solve() << endl;
    return 0;
}
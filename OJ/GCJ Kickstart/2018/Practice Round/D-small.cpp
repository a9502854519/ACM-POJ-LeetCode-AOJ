#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_N 510000

using namespace std;
typedef long long ll;

ll a[MAX_N];
ll bit[MAX_N];
int N, Q;

void add(int i, ll v){
    while(i <= N * (N + 1) / 2){
        bit[i] += v;
        i += i & -i;
    }
}
ll sum(int i){
    ll res = 0;
    while(i > 0){
        res += bit[i];
        i -= i & -i;
    }
    return res;
}
void init(vector<ll>& tmp){
    memset(bit, 0, sizeof(bit));
    for(int i = 0; i < tmp.size(); i++){
        add(i + 1, tmp[i]);
    }
}
void solve(){
    vector<ll> tmp;
    for(int i = 0; i < N; i++){
        ll s = 0;
        for(int j = i; j < N; j++){
            s += a[j];
            tmp.push_back(s);
        }
    }
    sort(tmp.begin(), tmp.end());
    init(tmp);
    int L, R;
    while(Q--){
        cin >> L >> R;
        cout << sum(R) - sum(L - 1) << endl;
    }
}
int main(){
    int T;
    cin >> T;
    for(int i = 1; i <= T; i++){
        cin >> N >> Q;
        for(int j = 0; j < N; j++){
            scanf("%d", a + j);
        }
        printf("Case #%d:\n", i);
        solve();
    }
    return 0;
}
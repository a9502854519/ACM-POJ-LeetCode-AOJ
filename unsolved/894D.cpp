#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_V 1000000 + 50
#define TEST

using namespace std;
typedef long long ll;

#ifdef TEST
    #include<ctime>
    using std::clock;
    using std::clock_t;
    clock_t S1, F1, S2, F2;
#endif

int n, m;
ll E[MAX_V];
vector<ll> Dis[MAX_V];
vector<ll> Sum[MAX_V];

void init(int v){
    int lch = 2 * v, rch = 2 * v + 1;
    int size_lch = 0, size_rch = 0;
    
    if(lch <= n){
        init(lch);
        Dis[v].push_back(E[2 * v - 1]);
        for(int i = 0; i < Dis[lch].size(); i++){
            Dis[v].push_back(E[2 * v - 1] + Dis[lch][i]);
        }
        size_lch = Dis[v].size();
    }
    if(rch <= n){
        init(rch);
        Dis[v].push_back(E[2 * v]);
        for(int i = 0; i < Dis[rch].size(); i++){
            Dis[v].push_back(E[2 * v] + Dis[rch][i]);
        }
        size_rch = Dis[v].size();
    }
    inplace_merge(Dis[v].begin(), Dis[v].begin() + size_lch, Dis[v].end());
    if(Dis[v].size() > 0){
        Sum[v].push_back(Dis[v][0]);
        for(int i = 1; i < Dis[v].size(); i++){
            Sum[v].push_back(Dis[v][i] + Sum[v][i - 1]);
        }
    }
}
ll calc(int v, ll H){
    //   v <-- u
    ll res = 0, d = 0;
    int last = -1;

    while(v > 0 && d < H){
        int lch = 2 * v, rch = 2 * v + 1;
        res += H - d;
        if(lch <= n && lch != last && H - d - E[2 * v - 1] > 0){
            int tmp = upper_bound(Dis[lch].begin(), Dis[lch].end(), H - d - E[2 * v - 1]) - Dis[lch].begin();
            res += H - d - E[2 * v - 1];
            if(tmp > 0){
                res += (H - d - E[2 * v - 1]) * tmp - Sum[lch][tmp - 1];
            }
        }
        
        if(rch <= n && rch != last && H - d - E[2 * v] > 0){
            int tmp = upper_bound(Dis[rch].begin(), Dis[rch].end(), H - d - E[2 * v]) - Dis[rch].begin();
            res += H - d - E[2 * v];
            if(tmp > 0){
                res += (H - d - E[2 * v]) * tmp - Sum[rch][tmp - 1];
            }
        }
        d += E[v - 1];
        last = v;
        v /= 2;
    }
    return res;
}
void solve(){
#ifdef TEST
    S1 = clock();
#endif
    int A;
    ll H;
    init(1);
#ifdef TEST
    F1 = clock();
    S2 = clock();
#endif
    while(m--){
        cin >> A >> H;
        cout << calc(A, H) << endl;
    }
#ifdef TEST
    F2 = clock();
    cout << "initializing time is " << double(F1 - S1) / CLOCKS_PER_SEC << endl;
    cout << "total query time is : " << double(F2 - S2) / CLOCKS_PER_SEC << endl;
#endif
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n - 1; i++){
        cin >> E[1 + i];
    }
    solve();
    return 0;
}

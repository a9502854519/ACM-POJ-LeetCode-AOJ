#include<iostream>
#include<cstdio>
#include<set>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAX_N 100000 + 100

using namespace std;
typedef long long ll;

ll n, w, bit[MAX_N];
struct Data{
    ll x, v;
    int id;
    Data() {}
    Data(ll x, ll v) : x(x), v(v) {}
    bool operator < (const Data& other) const{
        return llabs(x) * llabs(other.v + w) < llabs(other.x) * llabs(v + w);
    }
    bool operator == (const Data& other) const{
        return llabs(x) * llabs(other.v + w) == llabs(other.x) * llabs(v + w);
    }
    bool operator != (const Data& other) const{
        return !(*this == other);
    }
}p[MAX_N];

void add(int i){
    while(i <= n){
        bit[i] += 1;
        i += i & -i;
    }
}
ll sum(int i){
    ll s = 0;
    while(i > 0){
        s += bit[i];
        i -= i & -i;
    }
    return s;
}
bool cmp(const Data& a, const Data& b){
    ll i = llabs(a.x) * llabs(b.v - w), j = llabs(b.x) * llabs(a.v - w);
    if(i != j) return i < j;
    else if(i == j) return a.id > b.id;
}
void solve(){
    sort(p, p + n);
    p[0].id = 1;
    for(int i = 1; i < n; i++){
        p[i].id = p[i - 1].id + (p[i] != p[i - 1]);
    }
    sort(p, p + n, cmp);
    long long res = 0;
    for(int i = 0; i < n; i++){
        res += sum(n) - sum(p[i].id - 1);
        add(p[i].id);
    }
    cout << res << endl;
}
int main(){
    cin >> n >> w;
    for(int i = 0; i < n; i++){
        int x, v;
        scanf("%d %d", &x, &v);
        p[i] = Data(x, v);
    }
    solve();
    return 0;
}
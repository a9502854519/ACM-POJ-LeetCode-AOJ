#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<utility>
#include<vector>
#define MAX_N 10000 + 10
#define INF 1E18 + 1

using namespace std;
typedef long long ll;
typedef pair<ll, ll> P;
typedef vector<ll> vec;
typedef vector<vec> mat;

const ll MOD = 1e9 + 7;
ll s[3];
ll n, m;
struct Data{
    ll a, l, r;
    Data() {}
    Data(ll a, ll l, ll r) : a(a), l(l), r(r) {}
}p[MAX_N];

bool cmp(const Data& data1, const Data& data2){
    return data1.l < data2.l;
}
mat mul(mat A, mat B){
    mat C(3, vec(3));
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}
mat pow(mat A, ll n){
    mat B(3, vec(3));
    for(int i = 0; i < 3; i++) B[i][i] = 1;
    while(n > 0){
        if(n & 1) B = mul(B, A);
        A = mul(A, A);
        n >>= 1;
    }
    return B;
}
inline bool empty(){
    return (s[0] == -1 && s[1] == -1 && s[2] == -1);
}
inline P getmin(){
    P p = make_pair(-1, -1);
    for(int i = 0; i < 3; i++){
        if(s[i] > 0 && (p.first == -1 || s[i] < p.first)) p = make_pair(s[i], i + 3);
    }
    return p;
}
ll solve(){
    sort(p, p + n, cmp);
    s[0] = s[1] = s[2] = -1;
    vector<P> v;
    mat A(3, vec(3, 1)), res(3, vec(3, 0));
    A[0][2] = A[2][0] = 0;
    res[0][0] = res[1][1] = res[2][2] = 1;
    
    for(int i = 0; i < n || !empty(); i++){
        while(!empty()){
            P pr = getmin();
            if(i >= n || pr.first < p[i].l){
                v.push_back(pr);
                s[pr.second - 3] = -1;
            }else{
                break;
            }
        }
        if(i < n){
            if(s[p[i].a] == -1) v.push_back(make_pair(p[i].l, p[i].a));
            s[p[i].a] = max(s[p[i].a], p[i].r);
        }
    }
    ll k = 1;
    for(int i = 0; i <= v.size(); i++){
        ll nxt = i < v.size() ? v[i].first : m;
        res = mul(pow(A, nxt - k), res);
        k = nxt;
        if(i < v.size()){
            if(v[i].second >= 3){
                v[i].second -= 3;
                for(int j = 0; j < 3; j++) A[v[i].second][j] = 1;
                if(v[i].second % 2 == 0) A[v[i].second][2 - v[i].second] = 0;
            }else{
                for(int j = 0; j < 3; j++) A[v[i].second][j] = 0;
            }
        }
    }
    return res[1][1];
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> p[i].a >> p[i].l >> p[i].r;
        p[i].a--; p[i].l--;
    }
    cout << solve() << endl;
    return 0;
}
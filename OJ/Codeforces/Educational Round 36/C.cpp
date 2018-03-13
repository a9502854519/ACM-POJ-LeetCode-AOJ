#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define INF 5E18
using namespace std;
typedef long long ll;

string a, b;
bool used[20];

ll dfs(vector<ll>& ps, vector<ll>& qs, int i, ll sum, bool k){
    if(i == qs.size()) return sum;
    int last = -1;
    if(k){
        for(int j = ps.size() - 1; j >= 0; j--){
            if(!used[j]) sum = sum * 10 + ps[j];
        }
        return sum;
    }else{
        for(int j = ps.size() - 1; j >= 0; j--){
            if(qs[i] >= ps[j] && !used[j] && ps[j] != last){
                used[j] = true;
                ll res = dfs(ps, qs, i + 1, sum * 10 + ps[j], qs[i] > ps[j]);
                if(res < INF) return res;
                used[j] = false;
                last = ps[j];
            }
        }
        return INF;
    }
}
ll solve(){
    vector<ll> ps, qs;
    for(int i = 0; i < a.length(); i++){
        ps.push_back(a[i] - '0');
    }
    for(int i = 0; i < b.length(); i++){
        qs.push_back(b[i] - '0');
    }
    
    sort(ps.begin(), ps.end());
    ll res = 0;
    if(a.length() < b.length()){
        for(int i = ps.size() - 1; i >= 0; i--) res = res * 10 + ps[i];
    }else{
        res = dfs(ps, qs, 0, 0, false);
    }
    return res;
}
int main(){
    cin >> a >> b;
    cout << solve() << endl;
    return 0;
}
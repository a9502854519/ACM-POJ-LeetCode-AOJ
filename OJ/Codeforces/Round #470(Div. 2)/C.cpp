#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAX_N 100000 + 100

using namespace std;
typedef long long ll;

int N;
ll V[MAX_N], T[MAX_N], bit[MAX_N], sm[MAX_N];
ll bias[MAX_N];

void add(int i, ll v){
    while(i <= N){
        bit[i] += v;
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
void solve(){
    memset(bit, 0, sizeof(bit));
    memset(bias, 0, sizeof(bias));
    sm[0] = 0;
    for(int i = 1; i <= N; i++){
        sm[i] = sm[i - 1] + T[i];
    }
    for(int i = 1; i <= N; i++){
        int j = lower_bound(sm, sm + N + 1, V[i] + sm[i - 1]) - sm;
        add(i, 1);
        add(j + 1, -1);
        bias[j] += V[i] + sm[i - 1] - sm[j];
    }
    for(int i = 1; i <= N; i++){
        cout << T[i] * sum(i) + bias[i] << " ";
    }
    cout << endl;
}
int main(){
    cin >> N;
    for(int i = 1; i <= N; i++) scanf("%d", V + i);
    for(int i = 1; i <= N; i++) scanf("%d", T + i);
    solve();
    return 0;
}

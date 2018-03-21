#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAX_N 300000 + 10
#define MAX_A 1000000 + 10
#define MAX_DAT_SIZE (1 << 20) - 1

using namespace std;
typedef long long ll;

int n, m, dat_size;
int a[MAX_N];
int D[MAX_A];
ll dat[MAX_DAT_SIZE];
int two_cnt[MAX_DAT_SIZE];

void update(int i, int v){
    int k = i + dat_size - 1;
    dat[k] = v;
    two_cnt[k] = (v <= 2);
    while(k > 0){
        k = (k - 1) / 2;
        dat[k] = dat[2 * k + 1] + dat[2 * k + 2];
        two_cnt[k] = two_cnt[2 * k + 1] + two_cnt[2 * k + 2];
    }
}
void replace(int a, int b, int k, int l, int r){ // [a, b)
    if(b <= l || a >= r || two_cnt[k] == r - l){
        return; //全部都是2了，不用理它
    }
    if(r - l == 1){
        dat[k] = D[dat[k]];
        two_cnt[k] = dat[k] <= 2;
        return;
    }
    int lch = 2 * k + 1, rch = 2 * k + 2;
    replace(a, b, lch, l, (l + r) / 2);
    replace(a, b, rch, (l + r) / 2, r);
    dat[k] = dat[lch] + dat[rch];
    two_cnt[k] = two_cnt[lch] + two_cnt[rch];
}
void replace(int a, int b){ //[a, b]
    replace(a, b + 1, 0, 0, dat_size);
}
void init(){
    memset(D, 0, sizeof(D));
    D[1] = 1;
    for(int i = 1; i <= MAX_A; i++){
        for(int j = i; j <= MAX_A; j += i){
            D[j]++;
        }
    }
    
    memset(dat, 0, sizeof(dat));
    fill(two_cnt, two_cnt + sizeof(two_cnt) / sizeof(int), 1);
    dat_size = 1;
    while(dat_size < n) dat_size <<= 1;
    for(int i = 0; i < n; i++){
        update(i, a[i]);
    }
}
ll sum(int a, int b, int k, int l, int r){
    if(b <= l || a >= r) return 0;
    if(a <= l && b >= r) return dat[k];
    
    return sum(a, b, 2 * k + 1, l, (l + r) / 2) + 
           sum(a, b, 2 * k + 2, (l + r) / 2, r);
}
ll sum(int a, int b){ //[a, b]
    return sum(a, b + 1, 0, 0, dat_size);
}
void solve(){
    init();
    int t, l, r;
    while(m--){
        scanf("%d %d %d\n", &t, &l, &r);
        if(t == 1){
            replace(l - 1, r - 1);
            // for(int i = 0; i < n; i++){
                // cout << dat[i + dat_size - 1] << " ";
            // }
            // cout << endl;
        }else{
            printf("%I64d\n", sum(l - 1, r - 1));
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    solve();
    return 0;
}
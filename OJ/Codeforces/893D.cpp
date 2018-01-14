#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define MAX_N 100000
#define MAX_DAT_SIZE (1<<18) - 1
#define INF 1E9
using namespace std;

int n, d, sum[MAX_N];
int dat[MAX_DAT_SIZE], dat_size;
bool check[MAX_N];

void update(int x, int v){
    int k = x + dat_size - 1;
    dat[k] = v;
    while(k > 0){
        k = (k - 1) / 2;
        dat[k] = max(dat[2 * k + 1], dat[2 * k + 2]);
    }
}
void init(){
    dat_size = 1;
    while(dat_size < n) dat_size <<= 1;
    for(int i = 0; i < 2 * dat_size - 1; i++) dat[i] = -INF;
    for(int i = 0; i < n; i++){
        update(i, sum[i]);
    }
}
int query(int a, int b, int k, int l, int r){
    if(a >= r || b <= l) return -INF;
    if(a <= l && b >= r) return dat[k];
    
    int lch = 2 * k + 1, rch = 2 * k + 2;
    int r1 = query(a, b, lch, l, (l + r) / 2);
    int r2 = query(a, b, rch, (l + r) / 2, r);
    return max(r1, r2);
}
int query(int a, int b){
    return query(a, b, 0, 0, dat_size);
}
int solve(){
    init();
    int res = 0, cmp = 0;
    for(int i = 0; i < n; i++){
        if(sum[i] + cmp > d) return -1;
        if(check[i] && sum[i] + cmp < 0){
            res++;
            cmp += abs(sum[i] + cmp);
            int tmp = query(i + 1, n);
            if(d - tmp - cmp >= 0){
                cmp += min(d, d - tmp - cmp);
            }
        }
    }
    return res;
}
int main(){
    cin >> n >> d;
    memset(check, false, sizeof(check));
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        sum[i] = a;
        if(a == 0) check[i] = true;
        if(i > 0) sum[i] += sum[i - 1];
        // printf("%3d ", sum[i]);
    }
    // cout << endl;
    cout << solve() << endl;
    return 0;
}

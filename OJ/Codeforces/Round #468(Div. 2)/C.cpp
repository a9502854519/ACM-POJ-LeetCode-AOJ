#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define MAX_N 100000

using namespace std;

int x[MAX_N], n, cnt[3], y[3];

void solve(){
    sort(x, x + n);
    cnt[0] = cnt[1] = cnt[2] = 0;
    for(int i = 0; i < n; i++){
        cnt[x[i] - x[0]]++;
    }
    for(int i = 0; i < 3; i++) y[i] = x[0] + i;
    
    int tmp = min(cnt[2], cnt[0]); //往內移
    if(cnt[2] > 0 && cnt[1] / 2 > tmp) tmp = -cnt[1] / 2; //往外移
    
    cout << n - abs(tmp) * 2 << endl;
    for(int i = 0; i < cnt[0] - tmp; i++) cout << y[0] << " ";
    for(int i = 0; i < cnt[1] + 2 * tmp; i++) cout << y[1] << " ";
    for(int i = 0; i < cnt[2] - tmp; i++) cout << y[2] << " ";
    cout << endl;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%d", x + i);
    }
    solve();
    return 0;
}
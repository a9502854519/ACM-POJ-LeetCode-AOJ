#include<iostream>
#include<cstdio>
#include<queue>
#define MAX_N 1000 + 10

using namespace std;

int n;
int l[MAX_N], r[MAX_N];

void solve(){
    int last = 0;
    for(int i = 0; i < n; i++){
        if(last <= r[i]){
            printf("%d ", max(last, l[i]));
            last = max(last, l[i]) + 1;
        }else printf("0 ");
    }
    cout << endl;
}
int main(){
    int T;
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 0; i < n; i++){
            scanf("%d %d\n", l + i, r + i);
        }
        solve();
    }
    return 0;
}
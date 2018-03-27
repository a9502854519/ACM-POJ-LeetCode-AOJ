#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 200000 + 100

using namespace std;

int n, a[MAX_N];

void solve(){
    int y = a[0], x = a[0];
    for(int i = 1; i < n; i++){
        if(abs(a[i] - a[i - 1]) > 1){
            y = abs(a[i] - a[i - 1]);
            break;
        }else{
            y = max(y, a[i]);
        }
    }
    for(int i = 1; i < n; i++){
        x = max(x, a[i]);
        int tmp = abs(a[i] - a[i - 1]);
        if(tmp == 0 || (tmp == 1 && min(a[i], a[i - 1]) % y == 0) || (tmp > 1 && tmp != y)){
            cout << "NO\n";
            return;
        }
    }
    printf("YES\n%d %d\n", (x - 1) / y + 1, y);
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    solve();
    return 0;
}
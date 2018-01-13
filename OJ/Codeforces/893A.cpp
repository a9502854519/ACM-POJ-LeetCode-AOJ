#include<iostream>
#include<cstdio>
#define MAX_N 100

using namespace std;

int n;
int a[MAX_N];

void solve(){
    int s = 3;
    for(int i = 0; i < n; i++){
        if(s == a[i]){
            printf("NO\n");
            return;
        }
        s ^= a[i];
    }
    printf("YES\n");
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    solve();
}
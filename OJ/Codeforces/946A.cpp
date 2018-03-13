#include<iostream>
#include<cstdio>
#include<cmath>
#define MAX_N 100

using namespace std;

int n, a[MAX_N];

int solve(){
    int res = 0;
    for(int i = 0; i < n; i++){
        res += abs(a[i]);
    }
    return res;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    cout << solve() << endl;
    return 0;
}
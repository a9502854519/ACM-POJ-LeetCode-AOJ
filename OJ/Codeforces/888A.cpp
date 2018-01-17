#include<iostream>
#include<cstdio>
#define MAX_N 1000

using namespace std;

int n;
int a[MAX_N];

int solve(){
    int res = 0;
    for(int i = 1; i < n - 1; i++){
        res += (a[i] > a[i - 1] && a[i] > a[i + 1]) ||
               (a[i] < a[i - 1] && a[i] < a[i + 1]);
    }
    return res;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    cout << solve() << endl;
    return 0;
}
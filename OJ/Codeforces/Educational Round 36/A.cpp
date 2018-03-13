#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 100
#define INF 1E9

using namespace std;

int n, k, a;

int main(){
    cin >> n >> k;
    int mn = INF;
    for(int i = 0; i < n; i++){
        cin >> a;
        if(k % a == 0) mn = min(mn, k / a);
    }
    cout << mn << endl;
    return 0;
}
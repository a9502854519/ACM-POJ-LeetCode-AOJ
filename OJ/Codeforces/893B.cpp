#include<iostream>
#include<cstdio>

using namespace std;

int n;
int main(){
    cin >> n;
    int res, div;
    for(int i = 1;; i++){
        div = ((1 << i) - 1) << (i - 1);
        if(div > n) break;
        if(n % div == 0) res = div;
    }
    cout << res << endl;
}
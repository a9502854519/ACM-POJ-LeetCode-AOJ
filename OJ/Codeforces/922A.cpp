#include<iostream>
#include<cstdio>

using namespace std;

int x, y;

void solve(){
    //y - 1
    if(y == 0 || (y == 1 && x > 0) || x < y - 1 || (x - y + 1) % 2 == 1) puts("No");
    else puts("Yes");
}
int main(){
    cin >> x >> y;
    solve();
    return 0;
}
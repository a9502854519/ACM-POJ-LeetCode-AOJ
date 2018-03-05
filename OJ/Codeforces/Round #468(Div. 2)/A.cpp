#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int a, b;

int solve(){
    int mid = (a + b) / 2;
    int s = abs(mid - a), t = abs(mid - b);
    return (s + 1) * s / 2 + (t + 1) * t / 2;
}
int main(){
    cin >> a >> b;
    cout << solve() << endl;
    return 0;
}
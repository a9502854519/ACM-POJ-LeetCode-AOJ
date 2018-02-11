#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 360
#define INF 1E9

using namespace std;

int n, a[MAX_N], sum;

int solve(){
    int s = 0, t = 0;
    int res = INF, total = 0;
    while(s < n){
        if(total < sum / 2){
            total += a[t];
            t = (t + 1) % n;
        }
        else total -= a[s++];
        res = min(res, abs(sum - 2 * total));
    }
    return res;
}
int main(){
    cin >> n;
    sum = 0;
    for(int i = 0; i < n; i++){
        scanf("%d", a + i);
        sum += a[i];
    }
    cout << solve() << endl;
    return 0;
}
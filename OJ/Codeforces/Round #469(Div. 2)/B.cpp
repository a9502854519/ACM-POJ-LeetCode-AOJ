#include<iostream>
#include<cstdio>
#define MAX_N 100000

using namespace std;

int n, m;
int x[MAX_N], y[MAX_N];

int solve(){
    int pt1 = 0, pt2 = 0, sum1 = 0, sum2 = 0, res = 0;
    while(pt1 < n || pt2 < m){
        if(sum1 <= sum2 && pt1 < n){
            sum1 += x[pt1++];
        }else if(pt2 < m){
            sum2 += y[pt2++];
        }
        if(sum1 == sum2){
            sum1 = sum2 = 0;
            res++;
        }
    }
    return res;
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> x[i];
    for(int i = 0; i < m; i++) cin >> y[i];
    cout << solve() << endl;
    return 0;
}

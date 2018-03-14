#include<iostream>
#include<cstdio>

using namespace std;

int n;

int solve(){
    int res = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            int k = i ^ j;
            if((i + j) > k && (i + k) > j && (j + k) > i && k <= n){
                // printf("%d %d %d\n", i, j, k);
                res++;
            }
        }
    }
    return res / 3;
}
int main(){
    cin >> n;
    cout << solve() << endl;
    return 0;
}
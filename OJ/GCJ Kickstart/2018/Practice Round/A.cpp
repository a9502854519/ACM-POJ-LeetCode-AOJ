#include<iostream>
#include<cstdio>
#define MAX_N 500

using namespace std;

int a[MAX_N], b[MAX_N];
int N;

void solve(){
    int P;
    cin >> P;
    while(P--){
        int c;
        scanf("%d", &c);
        int res = 0;
        for(int i = 0; i < N; i++){
            res += ((a[i] <= c && c <= b[i]) || 
                    (b[i] <= c && c <= a[i]));
        }
        printf("%d ", res);
    }
    cout << endl;
}
int main(){
    int T;
    cin >> T;
    for(int i = 1; i <= T; i++){
        scanf("%d", &N);
        for(int j = 0; j < N; j++){
            scanf("%d %d", a + j, b + j);
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 100000 + 100

using namespace std;

string S, T;

int S_B[MAX_N], S_A[MAX_N];
int T_B[MAX_N], T_A[MAX_N];

void calc(string str, int *B, int *A){
    memset(B, 0, sizeof(B));
    memset(A, 0, sizeof(A));
    for(int i = 0; i < str.length(); i++){
        if(str[i] != 'A'){
            B[i + 1]++;
        }else{
            A[i + 1] = A[i] + 1;
        }
        B[i + 1] += B[i];
    }
}
void init(){
    calc(S, S_B, S_A);
    calc(T, T_B, T_A);
}
void solve(){
    init();
    
    int q;
    cin >> q;
    int a, b, c, d;
    string res;
    while(q--){
        scanf("%d %d %d %d\n", &a, &b, &c, &d);
        int B1 = S_B[b] - S_B[a - 1];
        int A1 = min(S_A[b], b - a + 1);
        int B2 = T_B[d] - T_B[c - 1];
        int A2 = min(T_A[d], d - c + 1);
        // printf("%2d %2d\n%2d %2d\n", B1, A1, B2, A2);
        if(B1 == B2 && A1 >= A2 && (A1 - A2) % 3 == 0){
            res += '1';
        }else if(B1 < B2 && (B2 - B1) % 2 == 0){
            if((B1 > 0 && A1 >= A2) || (B1 == 0 && A1 > A2)){
                res += '1';
            }else{
                res += '0';
            }
        }else{
            res += '0';
        }
    }
    cout << res << endl;
}
int main(){
    cin >> S >> T;
    solve();
}
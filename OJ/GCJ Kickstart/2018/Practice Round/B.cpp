#include<iostream>
#include<cstdio>

using namespace std;

int solve(long long K){
   while((K & 1) == 1){
       K >>= 1;
   }
   return ((K >> 1) & 1);
}
int main(){
    int T;
    long long K;
    cin >> T;
    for(int i = 1; i <= T; i++){
        cin >> K;
        printf("Case #%d: %d\n", i, solve(K - 1));
    }   
    return 0;
}
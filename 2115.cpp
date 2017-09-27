#include<iostream>
#include<cstdio>

using namespace std;

long long A, B, C, k;

long long extgcd(long long a, long long b, long long& x, long long& y){
    long long d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }else{
        x = 1, y = 0;
    }
    return d;
}
void solve(){
    //A + Cx = B (mod 2^k)
    long long n = (1LL<<k);
    long long a = C, b = B - A; //ax = b (mod n)
    long long d, x, y, x0;
    d = extgcd(a, n, x, y);
    if(b % d == 0){
            x0 = (x*b/d % n+n) % n;
            //printf("x0 = %lld\n", x0);
            for(int i = 0; i < d; i++){
                if((x0+i*n/d) % n < n/d){
                    cout<<(x0+i*n/d) % n<<endl;
                    break;
                }
            }
    }else{
        printf("FOREVER\n");
    }

}
int main(){
    while(scanf("%lld%lld%lld%lld", &A, &B, &C, &k) != EOF){
        //printf("%lld\n", solve());
        if(!A &&! B && !C && !k) break;
        solve();
    }
    return 0;
}

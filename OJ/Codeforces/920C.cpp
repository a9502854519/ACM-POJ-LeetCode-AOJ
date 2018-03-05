#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define MAX_N 200000 + 10

using namespace std;

int n, a[MAX_N];
char str[MAX_N];
int bit[MAX_N];

void add(int i, int v){
    while(i <= n){
        bit[i] += v;
        i += i & -i;
    }
}
int sum(int i){
    int s = 0;
    while(i > 0){
        s += bit[i];
        i -= i & -i;
    }
    return s;
}
bool solve(){
    memset(bit, 0, sizeof(bit));
    for(int i = 1; i <= n; i++){
        if(str[i - 1] == '0') add(i, 1);
    }
    for(int i = 1; i <= n; i++){
        if(a[i] != i && abs(sum(i - 1) - sum(a[i] - 1)) != 0){
            return false;
        }
    }
    return true;
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++) scanf("%d", a + i);
    scanf("%s", str);
    printf("%s\n", solve() ? "YES" : "NO");
    return 0;
}
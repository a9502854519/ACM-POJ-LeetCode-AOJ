#include<iostream>
#include<cstdio>
#define MAX_N 100

using namespace std;

int n;
int seq[MAX_N];
int ct[4];

int solve(){
    for(int i = 0; i < n; i++){
        ct[seq[i]]++;
    }
    
    return min(ct[0], ct[1]) * 2 + min(ct[2], ct[3]) * 2;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        char ch;
        cin >> ch;
        if(ch == 'U') seq[i] = 0;
        else if(ch == 'D') seq[i] = 1;
        else if(ch == 'L') seq[i] = 2;
        else seq[i] = 3;
    }
    cout << solve() << endl;
    return 0;
}
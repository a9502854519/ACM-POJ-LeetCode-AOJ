#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int n;
string s;

int solve(){
    for(int k = n / 2; k > 0; k--){
        int tmp = k;
        for(int i = 0; i + k < n; i++){
            if(s[i] == s[i + k]) tmp--;
            else break;
            
            if(tmp == 0){
                return n - k + 1;
            }
        }
    }
    return n;
}
int main(){
    cin >> n >> s;
    cout << solve() << endl;
    return 0;
}
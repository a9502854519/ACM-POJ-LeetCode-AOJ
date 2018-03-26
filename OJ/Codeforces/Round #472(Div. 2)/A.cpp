#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

string s;
int n, res;

bool solve(){
    bool res = false;
    for(int i = 0; i < s.length(); i++){
        if(i > 0 && s[i] != '?' && s[i] == s[i - 1]) return false;
        else if(s[i] == '?' && (i == 0 || s[i - 1] == '?' || i == n - 1 || s[i + 1] == '?' || s[i - 1] == s[i + 1])){
            res = true;
        }
    }
    return res;
}
int main(){
    cin >> n >> s;
    solve();
    printf("%s\n", solve() ? "Yes" : "No");
    return 0;
}
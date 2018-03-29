#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int n;
string s;

int solve(){
    int res = n;
    for(int i = 0; i < n - 1; i++){
        if((s[i] == 'U' && s[i + 1] == 'R') || 
           (s[i] == 'R' && s[i + 1] == 'U')){
               res--;
               i++;
        }
    }
    return res;
}
int main(){
    cin >> n >> s;
    cout << solve() << endl;
    return 0;
}
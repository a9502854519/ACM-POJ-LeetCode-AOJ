#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

string s;
int cnt[26];

void solve(){
    //2種：每種至少要 >= 2個
    //3種：至少要有一種 >= 2個
    //4種：沒特別限制
    vector<int> tmp;
    for(int i = 0; i < s.length(); i++) cnt[s[i] - 'a']++;
    for(int i = 0; i < 26; i++){
        if(cnt[i] > 0){
            tmp.push_back(cnt[i]);
        }
    }
    bool ok = false;
    if(tmp.size() == 2){
        ok |= tmp[0] >= 2 && tmp[1] >= 2;
    }else if(tmp.size() == 3){
        ok |= tmp[0] >= 2 || tmp[1] >= 2 || tmp[2] >= 2;
    }else if(tmp.size() == 4){
        ok = true;
    }
    cout << (ok ? "Yes" : "No") << endl;
}
int main(){
    cin >> s;
    solve();
    return 0;
}
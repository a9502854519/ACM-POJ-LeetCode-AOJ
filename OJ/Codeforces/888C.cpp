#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

string S;
int cnt[26];

bool check(int k){
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < k; i++){
        cnt[S[i] - 'a']++;
    }
    for(int i = k; i < S.length(); i++){
        if(cnt[S[i] - 'a'] > 0) cnt[S[i] - 'a']++;
        if(cnt[S[i - k] - 'a'] > 0) cnt[S[i - k] - 'a']--;
    }
    bool res = false;
    for(int i = 0; i < 26; i++) res |= cnt[i] > 0;
    return res;
}
int solve(){
    int ub = S.length(), lb = 0, mid;
    while(ub - lb > 1){
        mid = (ub + lb) / 2;
        if(check(mid)) ub = mid;
        else lb = mid;
    }
    return ub;
}
int main(){
    cin >> S;
    cout << solve() << endl;
    return 0;
}
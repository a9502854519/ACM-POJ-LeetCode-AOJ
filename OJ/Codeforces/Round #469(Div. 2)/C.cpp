#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#define MAX_N 200000

using namespace std;

string S;
vector<int> res[MAX_N];

void solve(){
    int n = S.length();
    queue<int> zero, one;
    int idx = 0;
    
    for(int i = 0; i < n; i++){
        if(S[i] == '0'){
            if(one.size() == 0){
                res[idx].push_back(i);
                zero.push(idx++);
            }else{
                res[one.front()].push_back(i);
                zero.push(one.front());
                one.pop();
            }
        }else{
            if(zero.size() == 0){
                cout << "-1\n";
                return;
            }else{
                res[zero.front()].push_back(i);
                one.push(zero.front());
                zero.pop();
            }
        }
    }
    if(one.size() > 0){
        cout << "-1\n";
        return;
    }
    cout << idx << endl;
    for(int i = 0; i < idx; i++){
        cout << res[i].size() << " ";
        for(int j = 0; j < res[i].size(); j++) cout << res[i][j] + 1 << " ";
        cout << endl;
    }
}
int main(){
    cin >> S;
    solve();
    return 0;
}
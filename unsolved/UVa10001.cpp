#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX_N 32

using namespace std;

int m, n;
char tmp[MAX_N];
int res[MAX_N], state[MAX_N];
int rule[8];
int code[8][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};


void parse_rule(){
    for(int i = 0; i < 8; i++){
        rule[i] = (m >> i) & 1;
    }
}
bool check(){
    bool a = true, b = true;
    for(int i = 0; i < n; i++){
        a &= (state[i] == 1);
        b &= (state[i] == 0);
    }
    return (a && m == 255) || (b && m == 0);
}
bool dfs(int i){
    if(i == n) return true;
    
    for(int j = 0; j < 8; j++){
        //try every rule
        if(rule[j] == state[i]){
            bool ok = true;
            for(int k = -1; k <= 1; k++){
                int p = (i + k + n) % n;
                if(res[p] != -1 && res[p] != code[j][k + 1]){
                    ok = false;
                    break;
                }
            }
            if(ok){
                vector<int> backup;
                for(int k = -1; k <= 1; k++){
                    int p = (i + k + n) % n;
                    backup.push_back(res[p]);
                    res[p] = code[j][k + 1];
                }
                if(dfs(i + 1)) return true;
                for(int k = -1; k <= 1; k++){
                    int p = (i + k + n) % n;
                    res[p] = backup[k + 1];
                }
            }
        }
    }
    return false;
}
void solve(){
    parse_rule();
    memset(res, -1, sizeof(res));
    for(int i = 0; i < n; i++){
        state[i] = tmp[i] - '0';
    }
    
    if(check()){
            cout << "REACHABLE\n";
    }else if(m != 0 && m != 255 && dfs(0)) cout << "REACHABLE\n";
    else cout << "GARDEN OF EDEN\n";
}
int main(){
    while(scanf("%d %d %s\n", &m, &n, tmp) != EOF){
        solve();
    }
    return 0;
}
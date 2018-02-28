#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<unordered_map>
#define MAX_N 10000 + 100

using namespace std;

vector<int> G[MAX_N];
vector<string> city;
int N, in[MAX_N];
unordered_map<string, int> mp;

void add_edge(int to, int from){
    G[to].push_back(from);
    in[from]++;
}
void dfs(int v){
    if(G[v].size() == 0){
        cout << endl;
        return;
    }
    cout << city[v] << "-" << city[G[v][0]] << " ";;
    dfs(G[v][0]);
}
void solve(){
    for(int i = 0; i <= N; i++){
        if(in[i] == 0){
            dfs(i);
            return;
        }
    }
}
void init(){
    for(int i = 0; i <= N; i++) G[i].clear();
    city.clear();
    mp.clear();
    memset(in, 0, sizeof(in));
}
int main(){
    int T;
    cin >> T;
    for(int i = 1; i <= T; i++){
        cin >> N;
        init();
        string a, b;
        int idx = 0;
        for(int j = 0; j < N; j++){
            cin >> a >> b;
            if(mp.find(a) == mp.end()){
                mp[a] = idx++;
                city.push_back(a);
            }
            if(mp.find(b) == mp.end()){
                mp[b] = idx++;
                city.push_back(b);
            }
            int u = mp[a], v = mp[b];
            add_edge(u, v);
        }
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
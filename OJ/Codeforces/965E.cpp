//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永無BUG
//
//
//
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<utility>
#include<algorithm>
#include<queue>
#define INF 1E9
#define MAX_N 100000 + 100

using namespace std;
typedef pair<int, int> P;
int trie[MAX_N][26];
int par[MAX_N], end[MAX_N], cnt, res;
priority_queue<P> que;

int insert(string& s){
    int node = 0;
    for(int i = 0; i < s.length(); i++){
        int t = s[i] - 'a';
        if(trie[node][t] == 0){
            trie[node][t] = ++cnt;
            par[cnt] = node;
        }
        node = trie[node][t];
    }
    end[node] = 1;
    return node;
}
void solve(){
    while(!que.empty()){
        P p = que.top(); que.pop();
        int d = p.first;
        p.second = par[p.second]; --p.first;
        while(p.second != 0 && end[p.second]){
            p.second = par[p.second];
            --p.first;
        }
        if(p.second > 0){//不能走到樹根，走到樹根就代表前綴長度0
            res -= (d - p.first);
            que.push(make_pair(p.first, p.second));
            end[p.second] = 1;
        }
    }
    cout << res << endl;
}
int main(){
    int n;
    cin >> n;
    string s;
    for(int i = 0; i < n; i++){
        cin >> s;
        int node = insert(s);
        //first  : 當前字串的深度(長度)
        //second : 當前字串在trie中的節點編號
        que.push(make_pair(s.length(), node));
        res += s.length();
    }
    solve();
    return 0;
}
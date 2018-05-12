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
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
#include<ctime>
#define MAX_N 1000010
#define MAX_LOG_V 20
// #define TIME

using namespace std;

#ifdef TIME
    clock_t S, F;
#endif

int n, k;
vector<int> G[MAX_N], res;
int depth[MAX_N], p[MAX_LOG_V][MAX_N], iter[MAX_N];
bool add[MAX_N], used[MAX_N];

void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
}
void dfs(){
    int par = -1, v = n - 1, d = 1;
    while(v != -1){
        if(!used[v]){
            p[0][v] = par;
            depth[v] = d;
            used[v] = true;
        }
        int& i = iter[v];
        bool finish = true;
        for(; i < G[v].size(); i++){
            if(!used[G[v][i]]){
                par = v;
                v = G[v][i];
                d++;
                finish = false;
                break;
            }
        }
        if(finish){
            v = p[0][v];
            d--;
        }
    }

}
void init(){
    dfs();
    // for(int i = 0; i < n; i++){
        // printf("p[%d] = %d\n", i + 1, p[0][i] + 1);
    // }
    for(int k = 0; k + 1 < MAX_LOG_V; k++){
        for(int v = 0; v < n; v++){
            if(p[k][v] < 0) p[k + 1][v] = -1;
            else p[k + 1][v] = p[k][p[k][v]];
        }
    }
}
int count(int v){
    int d = depth[v];
    int tmp = v;
    for(int k = MAX_LOG_V - 1; k >= 0; k--){
        if(p[k][v] != -1 && !add[p[k][v]]){
            // if(tmp == 2) printf("p[%d][%d] = %d\n", k, v + 1, p[k][v] + 1);
            v = p[k][v];
        }
    }
    return d - depth[v] + 1;
}
void get_path(int v, vector<int>& res){
    while(!add[v] && v != -1){
        res.push_back(v);
        v = p[0][v];
    }
}
void solve(){
    init();
    add[n - 1] = true;
    for(int v = n - 2, cnt = 1; v > 0 && cnt < n - k; v--){
        if(!add[v] && count(v) <= n - k - cnt){
            vector<int> tmp;
            get_path(v, tmp);
            if(tmp.size() <= n - k - cnt){
                cnt += tmp.size();
                for(auto& i : tmp) add[i] = true;
            }
        }
    }
    for(int i = 0; i < n; i++) if(!add[i]) printf("%d ", i + 1);
    cout << endl;
}
int main(){
#ifdef TIME
    S = clock();
#endif

    cin >> n >> k;
    for(int i = 0; i < n - 1; i++){
        int a, b;
        scanf("%d %d\n", &a, &b);
        add_edge(a - 1, b - 1);
    }
    solve();
    
#ifdef TIME
    F = clock();
    printf("%.3lf\n", double(F - S) / CLOCKS_PER_SEC);
#endif
    return 0;
}
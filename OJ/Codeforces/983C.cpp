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
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<cstring>
#include<ctime>
#include<algorithm>
#define MAX_N 2010 
#define time 
using namespace std;

struct P{
    int i, S, v;
    P() {}
    P(int i, int S, int v) : i(i), S(S), v(v) {}

    bool operator > (const P& other) const{
        return v > other.v;
    }
    
};
int n, in[MAX_N], out[MAX_N];
unordered_map<int, int> d[MAX_N];
priority_queue<P, vector<P>, greater<P> > que;

vector<int> parse(int S){
    vector<int> res;
    while(S > 0){
        res.push_back(S & (0xf));
        S >>= 4;
    }
    return res;
}
pair<int, int> next_state(vector<int>& tmp, int k){
    int res = k, cnt = tmp.size() - 1;
    for(int i = 0; i < tmp.size() - 1; i++){
        if(tmp[i] != k){
            res = (res << 4) | tmp[i];
            cnt--;
        }
    }
    return make_pair(res, cnt);
}
int next_state(vector<int>& tmp, int s, int t){
    int res = s;
    for(int i = 0; i < tmp.size() - 1; i++){
        res = (res << 4) | tmp[i];
    }
    res = (res << 4) | t;
    return res;
}
int solve(){
    d[0][1] = 0;
    que.push(P(0, 1, 0));
    while(!que.empty()){
        P p = que.top(); que.pop();
        int S = p.S, i = p.i;
        
        if(i == n && (S >> 4) == 0) return d[i][S];
        if(p.v > d[i][S]) continue;
       
        vector<int> tmp = parse(S);
        int cur = tmp.back();
        //送走電梯裡的人
        int pos[2] = {10, 0};//選出離目前位置最近的上下兩個目的地
        for(int k = 0; k < tmp.size() - 1; k++){
            if(tmp[k] >= cur) pos[0] = min(pos[0], tmp[k]);
            else pos[1] = max(pos[1], tmp[k]);
        }
        for(int k : pos){
            if(k == 10 || k == 0) continue;
            pair<int, int> _pair = next_state(tmp, k);
            int next = _pair.first, cnt = _pair.second;
            if(d[i].find(next) == d[i].end() || 
               d[i][next] > d[i][S] + abs(k - cur) + cnt){
                d[i][next] = d[i][S] + abs(k - cur) + cnt;
                que.push(P(i, next, d[i][next]));
            }
        }
        //去找下一個人
        if(tmp.size() < 5 && i < n){
            int next = next_state(tmp, in[i + 1], out[i + 1]);
            if(d[i + 1].find(next) == d[i + 1].end() || 
               d[i + 1][next] > d[i][S] + abs(in[i + 1] - cur) + 1){
                d[i + 1][next] = d[i][S] + abs(in[i + 1] - cur) + 1;
                que.push(P(i + 1, next, d[i + 1][next]));
            }
        }
    }
}
int main(){
#ifdef time
    clock_t S = clock();
#endif
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d %d\n", in + i, out + i);
    }
    cout << solve() << endl;
#ifdef time
    cout << "Running Time " << double(clock() - S) / CLOCKS_PER_SEC << "s\n";
#endif
    return 0;
}
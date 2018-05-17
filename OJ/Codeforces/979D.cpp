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
#include<set>
#include<utility>
#include<queue>
#include<cstring>
#include<algorithm>
#define MAX_DEPTH 17
#define MAX_N 100001

using namespace std;

struct Node{
    Node* next[2];
    int mn[2];
    Node() {
        next[0] = next[1] = NULL;
        mn[0] = mn[1] = 1e9;
    }
};
Node root[MAX_N];

void add(Node* node, int v){
    for(int i = MAX_DEPTH - 1; i >= 0; i--){
        int t = (v >> i) & 1;
        if(node->next[t] == NULL) node->next[t] = new Node;
        node->mn[t] = min(node->mn[t], v);
        node = node->next[t];
    }
}
int query(Node* node, int limit, int x){
    int res = 0;
    for(int i = MAX_DEPTH - 1; i >= 0; i--){
        int t = 1 - ((x >> i) & 1);
        if(node->next[t] == NULL || node->mn[t] > limit) t = 1 - t;
        if(node->next[t] == NULL || node->mn[t] > limit) return -1;
        node = node->next[t];
        res += (t << i);
    }
    return res;
}
void solve(){
    int q, t, u, x, k, s;
    cin >> q;
    while(q--){
        scanf("%d", &t);
        if(t == 1){
            scanf("%d", &u);
            for(int i = 1; i * i <= u; i++){
                if(u % i == 0){
                    add(root + i, u);
                    add(root + u / i, u);
                }
            }
        }else{
            scanf("%d %d %d", &x, &k, &s); // v <= s - x
            if(x % k != 0) printf("-1\n");
            else{
                cout << query(root + k, s - x, x) << endl;
            }
        }
    }
}
int main(){
    solve();
    return 0;
}
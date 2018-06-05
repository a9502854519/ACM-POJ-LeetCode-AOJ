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
#include<bits/stdc++.h>
#define MAX_N 100010
// #define TIME

using namespace std;

int n, a[MAX_N];
vector<int> G[MAX_N];
int dat[1 << 18], child_cnt[MAX_N];
int size_cnt[MAX_N];
set<pair<int, int> > s;
set<int> sz;

void build_dat(int k, int l, int r){
    if(r - l == 1){
        dat[k] = l;
        return;
    }
    int lch = 2 * k + 1, rch = 2 * k + 2;
    build_dat(lch, l, (l + r) / 2);
    build_dat(rch, (l + r) / 2, r);
    int left = dat[lch], right = dat[rch];
    dat[k] = a[left] > a[right] ? left : right;
}
int query(int c, int d, int k, int l, int r){
    if(r <= c || d <= l) return -1;
    if(c <= l && r <= d) return dat[k];
    int left = query(c, d, 2 * k + 1, l, (l + r) / 2), 
       right = query(c, d, 2 * k + 2, (l + r) / 2, r);
    return (right == -1 || (left != -1 && a[left] > a[right]) ? left : right);
}
int query(int c, int d){
    return query(c, d, 0, 0, n);
}
int build_tree(){
    int l = 0, r = n;
    queue<pair<int, int> > que;
    que.push({l, r});
    while(!que.empty()){
        tie(l, r) = que.front(); que.pop();
        int pivot = query(l, r);
        child_cnt[pivot] = 1;
        if(r - l > 1){
            if(l < pivot){
                int left = query(l, pivot);
                G[pivot].push_back(left);
                child_cnt[pivot] += pivot - l;
                que.push({l, pivot});
            }
            if(pivot + 1 < r){
                int right = query(pivot + 1, r);
                G[pivot].push_back(right);
                child_cnt[pivot] += r - pivot - 1;
                que.push({pivot + 1, r});
            }
        }
    }
    return query(0, n);
}
int init(){
    build_dat(0, 0, n);
    return build_tree();
}
void solve(){
    int pivot = init();
    pair<int, int> res = {0, 1e9};
    s.insert({a[pivot], pivot});
    sz.insert(n);
    size_cnt[n]++;
    while(!s.empty()){
        auto tmp = *prev(s.end());
        if(sz.size() == 1){
            if(s.size() > res.first || (s.size() == res.first && tmp.first < res.second)){
                res = {s.size(), tmp.first + 1};
            }
        }
        s.erase(tmp);
        if(--size_cnt[child_cnt[tmp.second]] == 0) sz.erase(child_cnt[tmp.second]);
        for(int to : G[tmp.second]){
            s.insert({a[to], to});
            size_cnt[child_cnt[to]]++;
            sz.insert(child_cnt[to]);
        }
    }
    cout << res.second <<endl;
}
int main(){
#ifdef TIME
    clock_t S = clock();
#endif
    //main program
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", a + i);
    solve();
#ifdef TIME
    printf("Running Time : %.3lfs\n", double(clock() - S) / CLOCKS_PER_SEC);
#endif
    return 0;
}
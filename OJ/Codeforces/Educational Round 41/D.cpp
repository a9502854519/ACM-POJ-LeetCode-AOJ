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
#include<algorithm>
#include<vector>
#define MAX_N 100000 + 10

using namespace std;
typedef long long ll;

struct P{
    ll x, y;
    P() {}
    P(ll x, ll y) : x(x), y(y) {}
    P operator - (const P& p) const{
        return P(x - p.x, y - p.y);
    }
    bool operator == (const P& p) const{
        return x == p.x && y == p.y;
    }
    bool operator != (const P& p) const{
        return x != p.x || y != p.y;
    }
    ll det(const P& p) const{
        return x * p.y - y * p.x;
    }
}ps[MAX_N];
int n;

bool cmp(const P& a, const P& b){
    if(a.x != b.x) return a.x < b.x;
    else return a.y < b.y;
}
vector<P> convex_hull(){
    int k = 0;
    vector<P> qs(n * 2);
    for(int i = 0; i < n; i++){
        while(k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    
    for(int i = n - 2, t = k; i >= 0; i--){
        while(k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}
bool same(P L1, P L2){
    return L1.det(L2) == 0;
}
bool solve(){
    if(n <= 4) return true;
    
    sort(ps, ps + n, cmp);
    
    vector<P> qs = convex_hull();
    if(qs.size() > 4) return false;

    for(int i = 0; i < qs.size(); i++){
        for(int j = i + 1; j < qs.size(); j++){
            
            int a = -1, b = -1;
            bool res = true;
            for(int k = 0; k < n; k++){
                if(ps[k] != qs[i] && ps[k] != qs[j]){
                    if(!same(ps[k] - qs[i], ps[k] - qs[j])){
                        if(a == -1) a = k;
                        else if(b == -1) b = k;
                        else{
                            if(!same(ps[k] - ps[a], ps[k] - ps[b])){ 
                                res = false;
                                break;
                            }
                        }
                    }
                }
            }
            if(res) return true;
        }
    }
    return false;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%I64d %I64d\n", &ps[i].x, &ps[i].y);
    }
    printf("%s\n", solve() ? "YES" : "NO");
    return 0;
}
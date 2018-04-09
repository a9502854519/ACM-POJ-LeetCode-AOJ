#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<utility>
#define MAX_N 100000 + 10
#define MAX_S (1 << 19)
#define MAX_A 70

using namespace std;
typedef pair<int, int> P;
typedef long long ll;

int n, a[MAX_N], ct[MAX_N];
ll dp[2][MAX_S];
bool used[MAX_S];
vector<int> s;
const int MOD = 1e9 + 7;
int table[71] = {
0,
0,
1,
2,
0,
4,
3,
8,
1,
0,
5,
16,
2,
32,
9,
6,
0,
64,
1,
128,
4,
10,
17,
256,
3,
0,
33,
2,
8,
512,
7,
1024,
1,
18,
65,
12,
0,
2048,
129,
34,
5,
4096,
11,
8192,
16,
4,
257,
16384,
2,
0,
1,
66,
32,
32768,
3,
20,
9,
130,
513,
65536,
6,
131072,
1025,
8,
0,
36,
19,
262144,
64,
258,
13,
};
void init(){
    sort(a, a + n);
    ll t = 1, idx = 0;
    for(int i = 0; i < n; i++){
        if(i < n - 1 && a[i] == a[i + 1]) t = (t * 2) % MOD;
        else{
            ct[idx++] = t;
            t = 1;
        }
    }
    unique(a, a + n);
    n = idx;
}
// int solve(){
    // init();
    // memset(dp, 0, sizeof(dp));
    // ll *cur = dp[0], *next = dp[1];
    // cur[0] = 1;
    // queue<P> que;
    // que.push(make_pair(0, 0));
    // for(int i = 0; i < n; i++){
        // P p;
        // while(que.front().first == i){
            // int v = que.front().second; que.pop();
            // if(cur[v] != 0){
                // next[v] = (next[v] + cur[v] * ct[i]) % MOD;
                // next[v ^ a[i]] = (next[v ^ a[i]] + cur[v] * ct[i]) % MOD;
                // que.push(make_pair(i + 1, v ^ a[i]));
                // que.push(make_pair(i + 1, v));
                // cur[v] = 0;
            // }
        // }
        // ll* tmp = cur;
        // cur = next;
        // next = tmp;
    // }
    // return cur[0] - 1;
// }
int solve(){
    ll res = 1;
    used[0] = true;
    s.push_back(0);
    for(int i = 0; i < n; i++){
        if(used[a[i]]) res = res * 2 % MOD;
        else{
            int tmp = s.size();
            for(int j = 0; j < tmp; j++){
                s.push_back(s[j] ^ a[i]);
                used[s[j] ^ a[i]] = true;
            }
        }
    }
    return res - 1;
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%I64d", a + i);
        a[i] = table[a[i]];
    }
    cout << solve() << endl;
    return 0;
}
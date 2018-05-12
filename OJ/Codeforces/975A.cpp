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
#include<queue>
#include<cstring>
#include<algorithm>
#include<set>
#define MAX_N 1000 + 100

using namespace std;

int n;
char str[MAX_N];

int main(){
    int res = 0;
    set<int> s;
    cin >> n;
    for(int i = 0; i < n; i++){
        scanf("%s", str);
        int tmp = 0;
        for(int j = 0; str[j] != '\0'; j++){
            tmp |= (1 << (str[j] - 'a'));
        }
        if(s.find(tmp) == s.end()) s.insert(tmp);
        
    }
    cout << s.size() << endl;
    return 0;
}
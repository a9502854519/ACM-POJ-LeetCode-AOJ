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
#include<cstring>
#include<algorithm>

using namespace std;

char n[20];
int digits;

bool square(int i){
    int tmp = sqrt(i);
    return tmp * tmp == i;
}
int solve(){
    digits = 0;
    for(int i = 0; n[i] != '\0'; i++) digits++;
    
    int res = 100;
    
    for(int i = 1; i < (1 << digits); i++){
        int sum = 0, cnt = 0;
        int j = digits - 1;
        for(int j = 0; j < digits; j++){
            if((i >> j) & 1){
                if(cnt > 0 || n[j] != '0'){
                    sum = sum * 10 + n[j] - '0';
                    cnt++;
                }
            }
        }
        // printf("i = %d  sum = %d\n", i, sum);
        if(cnt > 0 && square(sum)){
            // printf("cnt = %d\n", cnt);
            res = min(res, digits - cnt);
        }
    }
    return res == 100 ? -1 : res;
}
int main(){
    scanf("%s", n);
    cout << solve() << endl;
    return 0;
}
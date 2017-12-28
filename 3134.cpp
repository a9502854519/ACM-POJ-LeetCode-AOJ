#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 1024
#define MAX_D 20

using namespace std;

int exp[MAX_D] = {1}, ans[MAX_N];
/* 以下是我對hankcs大代碼的理解
 * exp[i]代表的是在搜索樹中，深度為i的數字
 * 像exp[0] = 1, exp[1] = 2, exp[2] = 3 or 4....etc
 * 這個算法會探索樹中的每一條路徑，用exp紀錄
 * 各個深度的數字。
 * 而剪枝策略是，先行計算每個數字的某種組
 * 合方式，用的是二進位的概念
 * 舉個例子, 31 = 11111
 * 要加到31，首先得加到16,然後再加8, 4, 2 ,1
 * 總步數為1)加到16的步數 = 4 + 2)加8, 4, 2, 1
 * 總共為8步。若超過這個步數，就可以剪枝了。
 * 總探索的節點數才88萬而已...
 * 只要碰到這類稍微難一點的搜索題，我就沒輒...囧
 */
void solve(int d){
	if(d > MAX_D) return;
	for(int i = 0; i <= d; i++){
		//嘗試目前所有可行的數字，往下一層前進
		exp[d + 1] = exp[i] + exp[d];
		if(exp[d + 1] < MAX_N && ans[exp[d + 1]] >= d + 1){
			ans[exp[d + 1]] = d + 1;
			solve(d + 1);
		}

		exp[d + 1] = exp[d] - exp[i];
		if(exp[d + 1] > 0 && ans[exp[d + 1]] >= d + 1){
			ans[exp[d + 1]] = d + 1;
			solve(d + 1);
		}
	}
}
int main(){
	for(int i = 2; i <= 1000; i++){
		ans[i] = __builtin_popcount(i) + (30 - __builtin_clz(i));
	}
	solve(0);
	int n;
	while(cin>>n && n){
		printf("%d\n", ans[n]);
	}
	return 0;
}

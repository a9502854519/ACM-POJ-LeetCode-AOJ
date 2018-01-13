/* 從第i個點出發的線，要和從第j個點出發的
　* 線不交叉的條件是，i的目的地f(i)和j的
　* 目的地f(j)要滿足f(i) < f(j)
　* 要找到一個序列，序列中的每個數字都滿足
　* 上述條件，LIS即為所求
 */　
#include<iostream>
#include<algorithm>
#define INF 10000000 
#define MAX_P 40000
using namespace std;

int dp[MAX_P];

int main(){
	int n,p,max,a;
	cin>>n;
	for(int t=0; t<n;t++){
		scanf("%d",&p);
		fill(dp,dp+p,INF);
		for(int i=0;i<p;i++) {
			scanf("%d",&a); 
			*lower_bound(dp,dp+p,a) = a;
		}
		cout<<lower_bound(dp,dp+p,INF)-dp<<endl;
	}
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
#define YEAR_OFFSET 1900
using  namespace std;

int Y, M, D;

int date_of_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool dp[102][13][32];

struct date{
	int  y, m, d;
	date() {}
	date(int y, int m, int d) : y(y), m(m), d(d) {}
};
int leap_date(int i, int j){
	i += YEAR_OFFSET;
	return (i % 4 == 0 && (i % 400 == 0 || i % 100 != 0)) && j == 2;
}
date get_next_day(int i, int j, int k){
	int days = date_of_month[j] + leap_date(i, j);
	k = k % days + 1;
	j = (j + (k == 1) - 1) % 12 + 1;
	i += (k == 1 && j == 1);
	return date(i, j, k);
}
date get_next_month(int i, int j, int k){
	j = j % 12 + 1;
	i += j == 1;
	if(k > date_of_month[j] + leap_date(i, j)) i = -1;
	return date(i, j, k);
}
void solve(){
	memset(dp, false, sizeof(dp));
	Y -= 1900;
	int i = Y, j = M, k = D;
	int days;
	while(i <= 101){
		printf("%d-%02d-%02d %s-->", i+1900, j, k,(dp[i][j][k] ? "true" : "false"));
		date next_date = get_next_day(i, j, k);
		if(next_date.y <= 101){
		       	dp[next_date.y][next_date.m][next_date.d] |= !dp[i][j][k];
			printf("\t%d-%02d-%02d  %s\n", next_date.y+1900, next_date.m, next_date.d, dp[next_date.y][next_date.m][next_date.d] ? "true" : "false");
		}
		next_date = get_next_month(i, j, k);
		if(next_date.y <= 101 && next_date.y != -1){
		       	dp[next_date.y][next_date.m][next_date.d] |= !dp[i][j][k];
			printf("\t\t\t%d-%02d-%02d %s\n", next_date.y+1900, next_date.m, next_date.d, dp[next_date.y][next_date.m][next_date.d] ? "true" : "false");
		}
		if(dp[101][11][4]){
			printf("YES\n");
			return;
		}else if( i == 101 && j == 11 && k > 4) break;
		cout<<endl;
		days = date_of_month[j] + leap_date(i, j);
		k = k % days + 1;
		j = (j + (k == 1) - 1) % 12 + 1;
		i += (j == 1 && k == 1);
	}	
	printf("NO\n");	

}
int main(){
	int T;
	cin>>T;
	while(T--){
		scanf("%d%d%d", &Y, &M, &D);
		solve();
	}
	return 0;
}


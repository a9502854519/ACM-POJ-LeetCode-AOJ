#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using  namespace std;

int Y, M, D;
const int date_of_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const static int YEAR_OFFSET = 1900; 

struct Date{
	int y, m, d, days;

	bool leap_date(){
		return (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)));
	}
	int get_day(){
		return date_of_month[m] + leap_date();
	}
	void correct_month(){
		while(m < 1){
			m += 12;
			y--;
		}
	}
	Date() : y(1900), m(1), d(1), days(31) {}
	Date(int yy, int mm, int dd) : y(yy), m(mm), d(dd) {
		correct_month();
		while(d < 1){
			m--;
			correct_month();
			d += (days = get_day());
		}
		while(d > (days = get_day())){
			d = days;
		}
	}

	Date  operator - (int v){
		return Date(y, m, d-v);
	}
	Date  operator >> (int v){
		Date temp(y, m-v, d);
		if(temp.d != d) return Date(y, m, d-1);
		return temp;
	}
	bool operator >= (const Date& other) const{
		return y > other.y || 
		       (y == other.y && m > other.m) ||
			   (y == other.y && m == other.m && d >= other.d);
	}
};
bool dp[102][13][32];


void solve(){
	memset(dp, 0, sizeof(dp));
	const Date start(Y, M, D);
	Date date(2001, 11, 4);
	while(date >= start){
		Date temp = date - 1;
		
		if(temp >= start){
			dp[temp.y-1900][temp.m][temp.d]  |= !dp[date.y-1900][date.m][date.d];
		}
		
		temp = date >> 1;
		if(temp >= start){
			dp[temp.y-1900][temp.m][temp.d] |= !dp[date.y-1900][date.m][date.d];
		}
		
		date = date - 1;
	}
	if(dp[Y-1900][M][D]) printf("YES\n");
	else printf("NO\n");
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
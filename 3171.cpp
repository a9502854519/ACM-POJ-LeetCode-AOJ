#include<iostream>
#include<cstdio>
#include<algorithm>
#define INF 50000000001
#define MAX_E 86400
typedef long long ll;
using namespace std;

struct Data{
	int T1, T2;
	ll 	S;
	bool operator < (const Data& other){
		return T1 < other.T1;
	}
}Cow[10000];

int N, M, E;
ll dp[MAX_E+1];//0~86400
ll dat[4*MAX_E];

void init(){
	fill(dat, dat+4*MAX_E, INF);
}
void update(ll v, int x, int k, int a, int b){		//[a, b)
	if(x < a || x >= b) return; //不在範圍內
	if(b - a == 1){//葉節點
		dat[k] = v;
		return;
	}
	update(v, x, 2*k+1, a, (a+b)/2);
	update(v, x, 2*k+2, (a+b)/2, b);
	dat[k] = min(dat[2*k+1], dat[2*k+2]);
}
void update(int x, ll v){
	update(v, x, 0, 0, E+1);
}
ll query(int a, int b, int l, int r, int k){
	if(b <= l || a >= r){
		return INF;
	}
	if(a <= l && b >= r){
		return dat[k];
	}
	ll v1 = query(a, b, l, (l+r)/2, 2*k+1);
	ll v2 = query(a, b, (l+r)/2, r, 2*k+2);
	return min(v1, v2);
}
ll query(int a, int b){//[a, b]
	return query(a, b+1, 0, E+1, 0);
}
int main(){
	scanf("%d%d%d", &N, &M, &E);
	for(int i = 0; i < N; i++){
		scanf("%d%d%lld", &Cow[i].T1, &Cow[i].T2, &Cow[i].S);
		Cow[i].T1 -= (M-1), Cow[i].T2 -= (M-1);
	}
	E -= (M-1), M = 1;
	sort(Cow, Cow+N);
	fill(dp, dp+86401, INF);
	dp[0] = 0;
	init();
	update(0, 0);
	
	for(int i = 0; i < N; i++){
		int T1 = Cow[i].T1, T2 = Cow[i].T2; ll S = Cow[i].S;
		ll v = query(T1-1, T2);
		
		if(dp[T2] > v + S){ 
			dp[T2] = v + S;
			update(T2, dp[T2]);
		}
	}
	
	if(dp[E] < INF) printf("%lld\n", dp[E]);
	else printf("-1\n");
	return 0;
}
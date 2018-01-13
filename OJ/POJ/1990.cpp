#include<iostream>
#include<algorithm>
#include<cstdio>
#define MAX_N 20000
typedef long long int ll;
using namespace std;

struct Moo{
	ll v;
	ll x;
	bool operator < (const Moo& other){
		return v < other.v || (v == other.v && x < other.x);
	}
};
Moo m[MAX_N + 1];

ll s[MAX_N + 1];
ll t[MAX_N + 1];

ll sum(ll *bit, int i){
	ll s = 0;
	while(i > 0){
		s += bit[i];
		i -= (i & -i);
	}
	return s;
}
void add(ll *bit, int i, ll x){ // 對第i個位置加上x
	while(i <= MAX_N){
		bit[i] += x;
		i += (i & -i);
	}
}
int main(){
	ll N;
	cin>>N;
	for(int i = 1; i <= N; i++){
		scanf("%lld %lld\n", &m[i].v, &m[i].x);
	}
	sort(m, m+N+1);
	fill(s, s+N+1, 0);
	fill(t, t+N+1, 0);
	add(t, m[1].x, 1);
	add(s, m[1].x, m[1].x);
	ll sum_s = m[1].x, sum_t = 1, res = 0;
	for(int i = 2; i <= N; i++){
		ll x = m[i].x,
			v = m[i].v, 
			t1 = sum(t, x-1), 
			s1 = sum(s, x-1); 
		res += v*(x*t1 - s1) + v*((sum_s - s1) - x*(sum_t - t1));
		add(t,x,1);
		add(s,x,x);
		sum_s += x;
		sum_t ++;
	}
	cout<<res<<endl;
	return 0;
}
	

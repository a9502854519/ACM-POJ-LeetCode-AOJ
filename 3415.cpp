#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAX_N 100000 * 2 + 100
#define MAX_DAT_SIZE (1<<19) - 1

using namespace std;
typedef long long  ll;

int K, k, n;
int rank[MAX_N + 1], tmp[MAX_N + 1];
int sa[MAX_N + 1], lcp[MAX_N + 1];
int L[MAX_N + 1], R[MAX_N + 1];
int st[MAX_N + 1];
int sum[MAX_N + 1];

string A, B;
void init_rmq(){
	memset(sum, 0, sizeof(sum));
	for(int i = 0; i <= n; i++){
		sum[i] = sa[i] >= A.length();
		if(i > 0) sum[i] += sum[i - 1];
	}
}
int query(int a, int b){
	return sum[b] - sum[a - 1];
}

bool compare_sa(int i, int j){
	if(rank[i] != rank[j]) return rank[i] < rank[j];
	else{
		int ri = i + k <= n ? rank[i + k] : -1;
		int rj = j + k <= n ? rank[j + k] : -1;
		return ri < rj;
	}
}
void construct_sa(string S){
	for(int i = 0; i <= n; i++){
		sa[i] = i;
		rank[i] = i < n ? S[i] : -1;
	}
	for(k = 1; k <= n; k *= 2){
		sort(sa, sa + n + 1, compare_sa);

		tmp[sa[0]] = 0;
		for(int i = 1; i <= n; i++){
			tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
		}
		for(int i = 0; i <= n; i++){
			rank[i] = tmp[i];
		}
	}
}
void construct_lcp(string S){
	for(int i = 0; i <= n; i++) rank[sa[i]] = i;

	int h = 0;
	lcp[0] = 0;

	for(int i = 0; i < n; i++){
		int j = sa[rank[i] - 1];

		if(h > 0) h--;
		for(; j + h <= n && i + h <= n; h++){
			if(S[i + h] != S[j + h]) break;
		}
		lcp[rank[i] - 1] = h;
	}
}
ll solve(){
	string S = A + '$' + B;
	n = S.length();
	construct_sa(S);
	construct_lcp(S);
	int m = A.length();
	int t = 0;
	for(int i = 0; i <= n; i++){
		while(t > 0 && lcp[ st[t - 1] ] > lcp[i]) t--;
		L[i] = (t == 0 ? 0 : st[t - 1] + 1);
		st[t++] = i;
	}

	t = 0;
	for(int i = n; i >= 0; i--){
		while(t > 0 && lcp[ st[t - 1] ] >= lcp[i]) t--;
		R[i] = (t == 0 ? n + 1 : st[t - 1]);
		st[t++] = i;
	}
	init_rmq();
	ll res = 0;
	for(int i = 0; i <= n; i++){
		if(lcp[i] >= K){		
			ll r1 = query(L[i], i);
			ll r2 = query(i + 1, R[i]);
			res += ((i + 1 - L[i] - r1) * r2 + r1 * (R[i] - i - r2)) * (lcp[i] - K + 1);
		}
	}
	return res;
}
void init(){
	memset(lcp, 0, sizeof(lcp));
}
int main(){
	while(cin>>K && K){
		init();
		cin>>A>>B;
		printf("%lld\n", solve());
	}
	return 0;
}




#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAX_N 50000 * 2 + 100

using namespace std;

int n, m, K, k;
vector<int> S;
int sa[MAX_N + 1], rank[MAX_N + 1], tmp[MAX_N + 1], lcp[MAX_N + 1], mcs[MAX_N + 1];

bool compare_sa(int i, int j){
	if(rank[i] != rank[j]) return rank[i] < rank[j];
	else{
		int ri = i + k <= n ? rank[i + k] : -2;
		int rj = j + k <= n ? rank[j + k] : -2;
		return ri < rj;
	}
}
void construct_sa(){
	for(int i = 0; i <= n; i++){
		sa[i] = i;
		rank[i] = i < n ? S[i] : -2;
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
void construct_lcp(){
	for(int i = 0; i <= n; i++) rank[sa[i]] = i;

	int h = 0;
	lcp[0] = 0;

	for(int i = 0; i < n; i++){
		int j = sa[rank[i] - 1];

		if(h > 0) h--;
		for(; j + h < n && i + h < n; h++){
			if(S[i + h] != S[j + h]) break;
		}
		lcp[rank[i] - 1] = h;
	}
}
void init(){
	memset(sa, 0, sizeof(sa));
	memset(lcp, 0, sizeof(lcp));
	memset(rank, 0, sizeof(rank));
	memset(mcs, 0, sizeof(mcs));
}
int solve(){
	init();
	m = n;
	n = S.size();
	construct_sa();
	construct_lcp();
	for(int j = 1; j <= n; j++){
		if(sa[j] > m){
			int t = lcp[j - 1];
			for(int i = j - 1; i >= 0 && sa[i] <= m; i--){
				t = min(t, lcp[i]);
				mcs[i] = t;
			}
		}
	}
	for(int j = n - 1; j >= 0; j--){
		if(sa[j] > m){
			int t = lcp[j];
			for(int i = j + 1; i <= n && sa[i] <= m; i++){
				mcs[i] = max(mcs[i], t);
				t = min(t, lcp[i]);
			}
		}
	}
	int res = 0;
	for(int i = 0; i <= n; i++){
		res += mcs[i] == K;
	}
	return res;
}
int main(){
	S.resize(MAX_N);
	while(scanf("%d %d %d\n", &n, &m, &K) != EOF){
		S.clear();
		for(int i = 0; i < n; i++){
			int a;
			scanf("%d", &a);
			S.push_back(a);
		}	
		S.push_back(-1);	
		for(int i = 0; i < m; i++){
			int a;
			scanf("%d", &a);
			S.push_back(a);
		}
		S.push_back(100001);
		printf("%d\n", solve());
	}
	return 0;
}

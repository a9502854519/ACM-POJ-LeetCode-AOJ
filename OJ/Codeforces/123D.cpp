#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define MAX_N 100000 + 100

using namespace std;
typedef long long ll;

string S;
int k, n;
int rank[MAX_N];
int sa[MAX_N];
int tmp[MAX_N];
int lcp[MAX_N];
int stv[MAX_N];
int stc[MAX_N];

bool compare_sa(int i, int j){
	if(rank[i] != rank[j]) return rank[i] < rank[j];
	else{
		int ri = i + k <= n ? rank[i + k] : -1;
		int rj = j + k <= n ? rank[j + k] : -1;
		return ri < rj;
	}
}
void construct_sa(){
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
void construct_lcp(){
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
	n = S.length();
	construct_sa();
	construct_lcp();
	/***
	for(int i = 0; i <= n; i++){
		printf("%2d %2d ", sa[i], lcp[i]);
		cout<<S.substr(sa[i])<<endl;
	}
	/***/
	ll res = 0, contribution = 0;
	int t = 0;
	for(int i = 1; i <= n; i++){
		res += (n - sa[i]);

		if(lcp[i] == 0){
			contribution = t = 0;
		}else{
			ll c = 1;
			while(t > 0 && stv[t - 1] >= lcp[i]){
				contribution -= stv[t - 1] * stc[t - 1];
				c += stc[t - 1];
				t--;
			}
			stv[t] = lcp[i];
			stc[t++] = c;
			contribution += lcp[i] * c;
			res += contribution;
		}
	}
	return res;
}
int main(){
	cin>>S;
	cout<<solve()<<endl;
	return 0;
}


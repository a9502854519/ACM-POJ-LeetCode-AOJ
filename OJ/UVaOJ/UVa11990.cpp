#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_N 200000
#define MAX_DAT_SIZE (1<<19) - 1

using namespace std;
typedef long long ll;

int n, m;
int dat_size;
ll res;
vector<int> bit0;
vector<int> dat[MAX_DAT_SIZE];
vector<int> bit1[MAX_DAT_SIZE];
int hsh[MAX_N + 1];
int data[MAX_N];

void add(vector<int>& bit, int i, int v, int n_){
	while(i <= n_){
		bit[i] += v;
		i += i & -i;
	}
}
int sum(vector<int>& bit, int i){
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}
int sum(vector<int>& bit, int a, int b){
	if(a > b) return 0;
	return sum(bit, b) - sum(bit, a - 1);
}
void init_dat(int k, int l, int r){
	dat[k].clear();
	if(r - l == 1){
		if(l < n){
		       	dat[k].push_back(data[l]);
			bit1[k].resize(2);
		}
		else{
			bit1[k].resize(1);
		}
		fill(bit1[k].begin(), bit1[k].end(), 0);
		return;
	}
	int lch = 2 * k + 1, rch = 2 * k + 2;
	init_dat(lch, l, (l + r) / 2);
	init_dat(rch, (l + r) / 2, r);
	dat[k].resize(dat[lch].size() + dat[rch].size());
	merge(dat[lch].begin(), dat[lch].end(), dat[rch].begin(), dat[rch].end(),
			dat[k].begin());
	bit1[k].resize(dat[k].size() + 1);
	fill(bit1[k].begin(), bit1[k].end(), 0);
}
int query_bigger(int a, int b, int k, int l, int r, int v){
	if(b <= l || a >= r) return 0;

	int idx = upper_bound(dat[k].begin(), dat[k].end(), v) - dat[k].begin();

	if(a <= l && b >= r){
		int temp = dat[k].size() - idx;
		temp -= sum(bit1[k], idx + 1, dat[k].size());
		return temp;
	}
	return query_bigger(a, b, 2 * k + 1, l, (l + r) / 2, v) + 
	       query_bigger(a, b, 2 * k + 2, (l + r) / 2, r, v);
}
int query_smaller(int a, int b, int k, int l, int r, int v){
	if(b <= l || a >= r) return 0;

	int idx = lower_bound(dat[k].begin(), dat[k].end(), v) - dat[k].begin();

	if(a <= l && b >= r){
		int temp = idx;
		temp -= sum(bit1[k], 1, idx);
		return temp;
	}
	return query_smaller(a, b, 2 * k + 1, l, (l + r) / 2, v) +
	       query_smaller(a, b, 2 * k + 2, (l + r) / 2, r ,v);
}
void remove(int x, int v){
	int k = x + dat_size - 1;
	int idx = lower_bound(dat[k].begin(), dat[k].end(), v) - dat[k].begin();
	add(bit1[k], idx + 1, 1, bit1[k].size());
	while(k > 0){
		k = (k - 1) / 2;
		idx = lower_bound(dat[k].begin(), dat[k].end(), v) - dat[k].begin();
		add(bit1[k], idx + 1, 1, bit1[k].size());
	}
}
void solve(){
	init_dat(0, 0, dat_size);
	int a;
	while(m--){
		printf("%lld\n", res);
		scanf("%d\n", &a);
		int idx = hsh[a]; //the position of a 
		int temp = query_bigger(0, idx + 1, 0, 0, dat_size, a) + query_smaller(idx, n, 0, 0, dat_size, a);
		res -= temp;
		remove(idx, a);
	}
}
void init(int n_){
	dat_size = 1;
	while(dat_size < n_) dat_size *= 2;
	bit0.resize(n + 1);
	fill(bit0.begin(), bit0.end(), 0);
	res = 0;
}

int main(){
	while(scanf("%d %d\n", &n, &m) != EOF){
		init(n);
		for(int i = 0; i < n; i++){
			scanf("%d\n", data + i);
			hsh[data[i]] = i;
			res += sum(bit0, data[i] + 1, n);
			add(bit0, data[i], 1, n);
		}
		solve();
	}
	return 0;
}

		






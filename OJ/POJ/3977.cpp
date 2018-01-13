#include<iostream>
#include<utility>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define INF 1E17
typedef long long int ll;
using namespace std;

bool pairCompare(const pair<ll, int>& firstElem, const pair<ll, int>& secondElem) {
	if(firstElem.first != secondElem.first)
		return firstElem.first < secondElem.first;
	else
		return firstElem.second < secondElem.second;
}

int main(){
	ll data[35];
	vector< pair<ll, int> > v;
	int n;
	while(cin>>n){
		if(n == 0) break;
		v.clear();
		for(int i = 0; i < n; i++) cin>>data[i];
		int n1 = n / 2;
		//將前半段完全列舉
		ll res = INF , m ;
		for(int i = 0; i < (1<<n1); i++){
			ll s = 0, count = 0;
			for(int j = 0; j < n1; j++){
				if((i>>j) & 1){
					s += data[j];
					count++;
				}
			}
			if(res > llabs(s) && count != 0){
				res = llabs(s);
				m = count;
			}
			v.push_back(make_pair(s, count));
		}
		v.push_back(make_pair(INF, 40));
		sort(v.begin(), v.end(),pairCompare);
		
		int n2 = n - n1;
		for(int i = 0; i < (1<<n2); i++){
			ll s = 0, count = 0;
			for(int j = 0; j < n2; j++){
				if((i>>j) & 1){
					s += data[n1 + j];
					count++;
				}
			}
			vector< pair<ll, int> >::iterator it = lower_bound(v.begin(), v.end(), make_pair(-s, 0));
			if(count + it->second != 0){
				if(llabs(it->first + s) > llabs((it-1)->first + s)) --it;
				if(res > llabs(it->first + s)){
					res = llabs(it->first + s);
					m = it->second + count;
				}else if(res == llabs(it->first + s)){
					m = min(m, it->second + count);
				}
			}
		}
		printf("%lld %lld\n", res, m);
	}
	return 0;
}
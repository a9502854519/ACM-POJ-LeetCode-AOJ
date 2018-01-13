#include<iostream>
#include<cstdio>
#include<queue>
#define MAX_N 20000

using namespace std;
typedef long long ll;

int N;

int main(){
	cin>>N;
	ll ans = 0;
	priority_queue< int, vector<int>, greater<int> > q;
	for(int i = 0; i < N; i++){
		int L;
		cin>>L;
		q.push(L);
	}
	while(q.size() > 1){
		int L1 = q.top(); q.pop();
		int L2 = q.top(); q.pop();
		ans += L1+L2;
		q.push(L1+L2);
	}
	printf("%lld\n", ans);
	return 0;
}
		
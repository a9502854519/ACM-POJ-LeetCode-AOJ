#include<iostream>
#include<cstdio>
#include<algorithm>
#include<utility>
#include<queue>
#define INF 1E9


#define MAX_PRIME 10000

using namespace std;

typedef pair<int, int> P;
bool is_prime[10001];
int cost [10000];
int par[10000];
void init(){
		fill(is_prime, is_prime + MAX_PRIME + 1, true);
		is_prime[0] = false, is_prime[1] = false;
		for(int i = 2;i<=MAX_PRIME; i++){
			if(is_prime[i]){
				for(int j = i * 2; j <= MAX_PRIME; j+=i) is_prime[j] = false;
			}
		}
}
void show(int n){
	
	if(par[n] == n) return;
	show(par[n]);
	cout<<n<<endl;
	
}
	
int main(){
	init();
	int T,a,b;
	cin>>T;
	priority_queue< P, vector<P>, greater<P> > q;
	for(int ct = 0; ct < T; ct++){
		while(!q.empty()) q.pop();
		cin>>a>>b;
		fill(cost, cost + 10000, INF);
		cost[a] = 0;
		q.push(P(0,a)); //first is the path length and second is the prime
		par[a] = a;
		while(!q.empty()){
			P p = q.top();
			q.pop();
			
			int n = p.second;
			
			
			if(n == b){
				cout<<cost[n]<<endl;
			//	show(n);
				break;
			}
			if(p.first > cost[n]) continue;
			
			
			for(int i = 1;i<=1000; i*=10){
				for(int j = 0; j < i * 10;j += i){
					int temp = (n / (i*10)) * (i * 10) + j + n % i;
					if(temp >= 1000 && is_prime[temp] && cost[n] + 1 < cost[temp]){
						cost[temp] = cost[n] + 1;
						par[temp] = n;
						q.push(P(cost[temp], temp));
					}
				}
			}
		}
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#include<utility>

using namespace std;

struct edge {int from, to, cost;};
edge es[5500];
int d[501];
void solve(int V, int E){
	for(int i=0;i<V;i++){
		for(int j=0;j<E;j++){
			edge e = es[j];
			if(d[e.to] > d[e.from] + e.cost){
				d[e.to] = d[e.from] + e.cost;
				if(i == V-1){
					cout<<"YES\n";
					return ;
				}
			}
		}
	}
	cout<<"NO\n";
}
int main(){
	int F,V,E,W;
	cin>>F;
	for(int fuck = 0 ; fuck < F; fuck++){
		cin>>V>>E>>W;
		for(int i = 0;i < 2*E;i+=2){
			int s,e,t;
			cin>>s>>e>>t;
			es[i].from = s;
			es[i].to   = e;
			es[i].cost = t;
			es[i+1].from = e;
			es[i+1].to   = s;
			es[i+1].cost = t;
		}
		for(int i = 2*E; i < 2*E+W; i++){
			int s,e,t;
			cin>>s>>e>>t;
			es[i].from = s;
			es[i].to   = e;
			es[i].cost = -t;
		}
		E = 2*E + W;
		solve(V,E);
	}
	return 0;
}
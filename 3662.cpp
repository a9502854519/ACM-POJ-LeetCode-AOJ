#include<iostream>
#include<queue>
#include<algorithm>
#include<cstdio>
#define MAX_V 1000
#define MAX_E 10000
#define INF 1E9
using namespace std;

struct Data{
	int A, B, L;
	bool operator < (const Data& other){
		return L < other.L;
	}
	bool operator > (const Data& other){
		return L > other.L;
	}
};
struct edge {int to, cost, id;};
struct P{
	int v, k; //v是頂點編號, k是使用了多少個編號大於x的邊
	
	bool operator > (const P& other)const{
		return k > other.k;
	}
};

int V, E, K;
vector<edge> G[MAX_V+1]; //1 ~ 1000
int d[MAX_V+1];
Data data[MAX_E+2];
P makeP(int v, int k){
	P p;
	p.v = v;
	p.k = k;
	return p;
}
bool C(int x){
	priority_queue< P, vector<P>, greater<P> > q;
	fill(d, d + V + 1, INF);
	d[1] = 0;
	P p;
	p.v = 1, p.k = 0;
	q.push(p);
	while(!q.empty()){
		p = q.top(); q.pop();
		int u = p.v;
		
		if(d[u] < p.k) continue;
		
		for(int i = 0; i < G[u].size(); i++){
			edge e = G[u][i];
			if(e.id <= x && d[e.to] > d[u] && d[u] <= K){
				d[e.to] = d[u];
				q.push(makeP(e.to, d[e.to]));
			}else if (e.id > x && d[e.to] > d[u] + 1 && d[u] < K){
				d[e.to] = d[u] + 1;
				q.push(makeP(e.to, d[e.to]));
			}
		}
	}
	return d[V] < INF;
}
int main(){
	cin>>V>>E>>K;
	
	for(int i = 1; i <= E; i++){
		cin>>data[i].A>>data[i].B>>data[i].L;
	}
	sort(data, data + E + 1);
	for(int i = 1; i <= E; i++){
		edge e;
		int u = data[i].A; e.to = data[i].B;
		e.id = i;
		G[u].push_back(e);
		e.to = data[i].A, u = data[i].B;
		G[u].push_back(e);
	}
	data[0].L = 0;
	data[E+1].L = -1;
	C(18);
	int ub = E + 1, lb = -1, mid;
	while(ub - lb > 1){
		mid = (ub + lb)/2;
		if(C(mid)) ub = mid;
		else lb = mid;
	}
	cout<<data[ub].L<<endl;
	return 0;
}
	
	
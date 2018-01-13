#include<iostream>
#include<algorithm>
#include<utility>
#include<queue>
#include<cstring>
#define INF 1E9
using namespace std;
struct edge {int to; int cost;};
typedef pair<int, int> P;
vector<edge> G[1001];
int d[1001];
int w[1001];
int main(){
	int V,E,s,a,b,t,sum;
	edge temp;
	cin>>V>>E>>s;
	for(int i=0;i<E;i++){
		cin>>a>>b>>t;
		temp.to = b, temp.cost = t;
		G[a].push_back(temp);
	}
	priority_queue< P, vector<P>, greater<P> > q;
	fill(d,d+V+1,INF);
	d[s] = 0;
	q.push(P(d[s],s));
	//先算從會場到各農場的距離
	while(!q.empty()){
		P p = q.top(); q.pop();
		int v = p.second;
		if(d[v] < p.first) continue;
		for(int i=0;i<G[v].size();i++){
			edge e = G[v][i];
			if(d[e.to] > d[v] + e.cost){
				d[e.to] = d[v] + e.cost;
				q.push(P(d[e.to], e.to));
			}
		}
	}
	//for(int i=1;i<=V;i++) cout<<d[i]<<(i==V ? "\n" : " ");
	//再算從各農場到會場的距離
	sum = 0;
	for(int i=1;i<=V;i++){
		if(i!=s){
			fill(w, w+V+1, INF);
			w[i] = 0;
			while(!q.empty()) q.pop();
			q.push(P(w[i], i));
			while(!q.empty()){
				P p = q.top(); q.pop();
				int v = p.second;
				if(v == s){
					break;
				}
				
				if(w[v] < p.first) continue;
				for(int j=0;j<G[v].size(); j++){
					edge e = G[v][j];
					if(w[e.to] > w[v] + e.cost){
						w[e.to] = w[v] + e.cost;
						q.push(P(w[e.to], e.to));
					}
				}
			}
			//for(int j=1;j<=V;j++) cout<<w[j]<<(j==V ? "\n" : " ");
			sum = max(sum ,d[i] + w[s]);
		}
	}
	cout<<sum<<endl;
	return 0;
}
		
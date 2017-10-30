/* 這題比較難懂，意思是，電話公司可以免費提供Ｋ條
 * 電話線，長度隨意。如果使用了超過Ｋ條線，則必須
 * 支付一筆費用，該費用等於多出來的電話線中，最長
 * 的電話線長度。
 * 最長的最小，很容易聯想到二分搜尋。問題就可以轉
 * 換成，能不能將成本壓在某個數字x內。為了將成本
 * 最小化，當然會希望通過的邊盡量少，因此可以轉換
 * 成最短路問題。
 * 如果通過的邊的長度超過x，則將其算進免費的扣打內
 * ，令d[v] = 從起點走到v，使用的扣打數量。如果走到
 * 終點時，使用的扣打不超過Ｋ，就代表可行。
 */
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
	bool operator < (const Data& other) const{
		return L < other.L;
	}
};
struct edge {
	int to, cost;
	edge() {}
	edge(int to, int  cost) : to(to), cost(cost) {}	
};
struct P{
	int v, k; 
	
	bool operator > (const P& other) const{
		return k > other.k;
	}
	P() {}
	P(int v, int  k) : v(v), k(k) {}
};

int V, E, K;
vector<edge> G[MAX_V+1]; //1 ~ 1000
int d[MAX_V+1];
Data data[MAX_E+2];


bool C(int x){
	priority_queue< P, vector<P>, greater<P> > q;
	fill(d, d + V + 1, INF);
	d[1] = 0;
	q.push(P(1, d[1]));

	while(!q.empty()){
		P p = q.top(); q.pop();
		int u = p.v;
		
		if(d[u] < p.k) continue;
		
		for(int i = 0; i < G[u].size(); i++){
			edge e = G[u][i];
			int cost = d[u] + (e.cost > x ? 1 : 0);
			if(d[e.to] > cost){
				d[e.to] = cost;
				q.push(P(e.to, cost));
			}
		}
	}
	return d[V] <= K;
}
void add_edge(int from, int to, int id){
	G[from].push_back(edge(to, id));
	G[to].push_back(edge(from, id));
}

void solve(){
	sort(data, data + E + 1);

	data[0].L = 0;
	data[E+1].L = -1;

	int ub = E + 1, lb = -1, mid;
	while(ub - lb > 1){
		mid = (ub + lb)/2;
		if(C(data[mid].L)) ub = mid;
		else lb = mid;
	}
	cout<<data[ub].L<<endl;
}
int main(){
	cin>>V>>E>>K;
	
	for(int i = 1; i <= E; i++){
		cin>>data[i].A>>data[i].B>>data[i].L;
		add_edge(data[i].A, data[i].B, data[i].L);
	}
	solve();
	return 0;
}

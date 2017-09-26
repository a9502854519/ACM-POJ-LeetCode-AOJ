/* 有M個箱子，考慮最壞的情況：全都塞第一個箱子。
 * 再來考慮如何節省開支。如果能把某個從第一個箱
 * 子取出來的球，放進其它空的箱子，然後等待下一
 * 個同號的球到來，就能節省開支了。
 * 對於每個相鄰的狀態建邊(INF/0)，表示保持空箱狀
 * 態；對於相同序號的狀態a和b，在a的下一個狀態和
 * b之間建一條邊(-w/1)，表示在取出該球後，放進某一
 * 空箱子，然後直接快轉到下個同序號的球時候。權重
 * 表示省下的費用。
 * 取M-1最小費用流。因為我們一開始就已經有一個箱子
 * 有放球了。剩下M-1個箱子是用來省費用的。
 *
 * 後記：這題真是天殺難...AOJ上不包含我，只有43
 * 個人過，AC率只有24%。靠北難囧。
 */
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<utility>
#include<cstring>
#define INF 1000000000
#define MAX_V 10000

using namespace std;
typedef pair<int, int> P;

struct edge{
	int to, cap, cost, rev;
	edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};
int N, M, K, V;
vector<edge> G[MAX_V];
int dist[MAX_V];
int prevv[MAX_V], preve[MAX_V];

void add_edge(int from, int to, int cap, int cost){
	G[from].push_back(edge(to, cap, cost, G[to].size()));
	G[to].push_back(edge(from, 0, -cost, G[from].size()-1));
}

int min_cost_flow(int s, int t, int f){
	int res = 0;
	while(f > 0){
		//Bellman-Ford
		fill(dist, dist+V, INF);
		dist[s] = 0;
		bool update = true;
		while(update){
			update = false;
			for(int v = 0; v < V; v++){
				if(dist[v] == INF) continue;
				for(int i = 0; i < G[v].size(); i++){
					edge &e = G[v][i];
					if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
						dist[e.to] = dist[v] + e.cost;
						prevv[e.to] = v;
						preve[e.to] = i;
						update = true;
					}
				}
			}
		}
		if(dist[t] == INF){
			return -1;
		}
		int d = f;
		for(int v = t; v != s; v = prevv[v]){
			d = min(d, G[prevv[v]][preve[v]].cap);
		}
		f -= d;
		res += dist[t];
		for(int v = t; v != s; v = prevv[v]){
			edge &e = G[prevv[v]][preve[v]];
			e.cap -= d;
			G[v][e.rev].cap += d;
		}
	}
	return res;
}
int w[MAX_V], s[MAX_V], last[MAX_V];
int main(){
	cin>>M>>N>>K;
	int sum = 0;
	for(int i = 0; i < N; i++) scanf("%d", &w[i]);
	int index = 0;
	for(int i = 0; i < K; i++){
		scanf("%d", &s[index]);
		if(index == 0 || s[index] != s[index-1]){
			sum += w[s[index]-1];
			index++;
		}
	}
	V = index;
	memset(last, -1 ,sizeof(last));
	for(int i = 0; i < V; i++){
		if(last[s[i]] >= 0) add_edge(last[s[i]] + 1, i, 1, -w[s[i]-1]);
		if(i < V-1) add_edge(i, i+1, INF, 0);
		last[s[i]] = i;
	}
	printf("%d\n",sum + min_cost_flow(0, V-1, M-1));
	return 0;
}
	
	
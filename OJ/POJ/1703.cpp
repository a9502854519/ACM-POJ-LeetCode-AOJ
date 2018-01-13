#include<iostream>
#include<cstdio>

using namespace std;
int par[100001];
int rank[100001];
int enemy[100001];
void init (int n){
	for(int i=1;i<=n;i++){
		par[i] = i;
		rank[i] = 0;
	}
}
int find(int x){
	if(par[x] == x)
		return x;
	else 
		return par[x] = find(par[x]);
}
void unite(int x, int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(rank[x] < rank[y])
		par[x] = y;
	else{
		par[y] = x;
		if(rank[x] == rank[y]) rank[x]++;
	}
}
bool same(int x, int y){
	return find(x) == find(y);
}
int main(){
	int T,N,M,p,q;
	char ch;
	cin>>T;
	for(int count = 0; count < T;count++){
		scanf(" %d %d",&N,&M);
		init(N);
		fill(enemy, enemy+N+1, -1);
		for(int i=0;i<M;i++){
			scanf(" %c%d%d",&ch,&p,&q);
			if(ch == 'D'){
				if(enemy[p] == -1) enemy[p] = q;
				if(enemy[q] == -1) enemy[q] = p;
				unite(p,enemy[q]);
				unite(q,enemy[p]);
			}else{
				if(same(p,q)) printf("In the same gang.\n");
				else{
					if(enemy[p] != -1 && enemy[q] != -1 && (same(p,enemy[q]) || same(q, enemy[p])))
						printf("In different gangs.\n");
					else
						printf("Not sure yet.\n");
				}
			}
			
		}
	}
	return 0;
}
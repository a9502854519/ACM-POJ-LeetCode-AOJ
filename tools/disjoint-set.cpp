int par[MAX_N]; //父節點的編號
int rank[MAX_N]; //樹的高度

void init(){
	for(int i = 0; i < n; i++){
		par[i] = i; //一開始，每個節點的父節點就是自己
		rank[i] = 0;
	}
}
//查詢元素x所在的樹的根
int find(int x){
	if(par[x] == x){
		return x; //到根節點了
	}else{
		//在查詢的過程中，直接將子節點通通指向父節點，節省之後的查詢時間
		return par[x] = find(par[x]);
	}
}
//合併x和y所在的集合
void unite(int x, int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(rank[x] < rank[y]){
		par[x] = y;//將x指向y
	}else{
		par[y] = x;
		if(rank[x] == rank[y]) rank[x]++;
	}
}
//查詢x和y是否屬於同一集合
bool same(int x, int y){
	return find(x) == find(y);
}
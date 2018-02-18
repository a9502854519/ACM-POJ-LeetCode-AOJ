#include<iostream> 
#include<cstdio> 
#include<algorithm>
#include<vector>
#define MAX_V 500000 + 10

using namespace std;

struct edge{
    int to, from, w;
    
    edge() {}
    edge(int to, int from, int w) : to(to), from(from), w(w) {}
    bool operator < (const edge& other) const{
        return w < other.w;
    }
};
struct Data{
    edge e;
    int id;
    Data() {}
    Data(edge e, int id) : e(e), id(id) {}
    bool operator < (const Data& other) const{
        if(e.w != other.e.w) return e.w < other.e.w;
        else return id < other.id;
    }
};
vector<edge> E;
vector<Data> D;
bool result[MAX_V];
int n, m, q;
int par[MAX_V];
int rank[MAX_V];
int st[MAX_V], t;


inline void add_edge(int to, int from, int w){
    E.push_back(edge(to, from, w));
}
void init(){
    for(int i = 0; i < n; i++){
        par[i] = i;
        rank[i] = 0;
    }
    for(int i = 0; i < q; i++) result[i] = true;
}
int find(int x){
	if(par[x] == x){
		return x; //到根節點了
	}else{
		return find(par[x]);
	}
}
//合併x和y所在的集合
void unite(int x, int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(rank[x] < rank[y]){
		par[x] = y;//將x指向y
        st[t++] = x;
	}else{
		par[y] = x;
        st[t++] = y;
		if(rank[x] == rank[y]) rank[x]++;
	}
}
void goback(){
    while(t > 0){
        int x = st[--t];
        par[x] = x;
    }
}
//查詢x和y是否屬於同一集合
bool same(int x, int y){
	return find(x) == find(y);
}
void solve(){
    sort(E.begin(), E.end());
    sort(D.begin(), D.end());
    init();
    // for(int i = 0; i < E.size(); i++){
        // printf("%d %d %d\n", E[i].to, E[i].from, E[i].w);
    // }
    // for(int i = 0; i < D.size(); i++){
        // edge e = D[i].e;
        // printf("%2d : %d %d %d %d\n", i, e.to, e.from, e.w, D[i].id);
    // }
    for(int i = 0, j = 0; i < E.size() || j < D.size(); ){
        t = 0;
        while(E[i].w == D[j].e.w){
            for(int k = D[j].id; D[j].id == k && E[i].w == D[j].e.w && j < D.size(); j++){
                edge e = D[j].e;
                if(same(e.to, e.from)){
                    result[D[j].id] = false;
                }else{
                    unite(e.to, e.from);
                }
            }
            goback();
        }
        for(; i < E.size() && E[i].w != D[j].e.w; i++){
            unite(E[i].to, E[i].from);
        }
    }
    for(int i = 0; i < q; i++){
        if(result[i]) puts("YES");
        else puts("NO");
    }
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int to, from, w;
        scanf("%d %d %d\n", &to, &from, &w);
        add_edge(to - 1, from - 1, w);
    }
    cin >> q;
    for(int i = 0; i < q; i++){
        int k;
        scanf("%d", &k);
        while(k--){
            int tmp;
            scanf("%d", &tmp);
            D.push_back(Data(E[tmp - 1], i));
        }
    }
    solve();
    return 0;
}
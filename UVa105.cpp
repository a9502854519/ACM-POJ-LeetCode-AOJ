#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>
#include<utility>

using namespace std;
typedef pair<int, int> P;

int n;

struct E{
	int id, x, H;
	bool start;
	E() {}
	E(int id, int x, int H, bool start) : id(id), x(x), H(H), start(start) {}
	bool operator < (const E& b) const{
		if(x != b.x) return x < b.x;
		if(x == b.x){
			if(start && b.start){
				return H > b.H;
			}else if(!start && !b.start){
				return H < b.H;
			}else{
				if(start) return true;
				else       return false;
			}
		}
	}
};
struct D{
	int L, H, R;
	D() {}
	D(int L, int H, int R) : L(L), R(R), H(H) {}
};
vector<D> data;
vector<E> event;

bool cmp(const E& a, const E& b){
}
void solve(){
	int n = data.size();
	for(int i = 0; i < n; i++){
		event.push_back(E(i, data[i].L, data[i].H, true));
		event.push_back(E(i, data[i].R, data[i].H, false));
	}
	sort(event.begin(), event.end());

	set<P> s;
	vector<int> res;
	int cur_height = 0;
	for(int i = 0; i < event.size(); i++){
		E e = event[i];
		if(e.start){ //start
			s.insert(P(e.H, e.id));
			if(cur_height != (*s.rbegin()).first){
				cur_height = (*s.rbegin()).first;
				res.push_back(e.x);
				res.push_back(cur_height);
			}
		}else{
			s.erase(P(e.H, e.id));
			if(s.size() == 0){
				cur_height = 0;
				res.push_back(e.x);
				res.push_back(cur_height);
			}else if(cur_height != (*s.rbegin()).first){
				cur_height = (*s.rbegin()).first;
				res.push_back(e.x);
				res.push_back(cur_height);
			}
		}
	}		
	for(int i = 0; i < res.size(); i++){
		printf("%d%c", res[i], i == res.size() - 1 ? '\n' : ' ');
	}

	
}
int main(){
	int L, H, R;
	while(scanf("%d %d %d", &L, &H, &R) != EOF){
		data.push_back(D(L, H, R));
	}
	solve();
	return 0;
}

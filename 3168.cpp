#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<cstring>
#define MAX_N 25001
#define MAX_L 1000001

using namespace std;

int N;
int x1[MAX_N], y1[MAX_N], x2[MAX_N], y2[MAX_N];
int list_id[MAX_L];
bool touched[MAX_N], list[MAX_L];
struct check_p{
	int x, y1, y2, id;
	check_p() {}
	check_p(int x, int y1, int y2, int id) : x(x), y1(y1), y2(y2), id(id) {}
	bool operator < (const check_p& other) const{
		if(x != other.x) return x < other.x;
		else if ((id < N && other.id < N) || (id >= N && other.id >= N)) return y1 < other.y1;
		else return id > other.id;
	}
};
void solve(){
	memset(touched, 0, sizeof(touched));
	//列舉檢查點
	vector<check_p> events;
	for(int i = 1; i <= N; i++){
		events.push_back(check_p(x1[i], y1[i], y2[i], i));
		events.push_back(check_p(x2[i], y1[i], y2[i], i+N));
	}
	sort(events.begin(), events.end());
	vector< pair<int, int> > removed;
	memset(list, 0, sizeof(list));
	memset(list_id, 0, sizeof(list_id));
	for(int i = 0; i < events.size(); i++){
		if(i > 0 && events[i].x != events[i-1].x) removed.clear();
		int id = events[i].id;
		if(id > N) id -= N;
		if(events[i].id <= N){
			if(list[events[i].y1] == true){
				touched[id] = true, touched[list_id[events[i].y1]] = true;
			}
			if(list[events[i].y2] == true){
				touched[id] = true, touched[list_id[events[i].y2]] = true;
			}
			list[events[i].y1] = true, list[events[i].y2] = true;
			list_id[events[i].y1] += id, list_id[events[i].y2] += id;
			vector< pair<int, int> >::iterator it = lower_bound(removed.begin(), removed.end(), make_pair(events[i].y1, 0));
			
			for(; it != removed.end(); it++){
				int rm_id = it->second;
				if(y2[rm_id] >= y1[id] && y1[rm_id] <= y2[id]){
					touched[id] = true, touched[rm_id] = true;
				}else if (y1[rm_id] > y2[id]){
					break;
				}
			} 
		}else{
			list_id[events[i].y1] -= id, list_id[events[i].y2] -= id;
			list[events[i].y1] = (list_id[events[i].y1] > 0), list[events[i].y2] = (list_id[events[i].y2] > 0);
			removed.push_back(make_pair(events[i].y1, id));
			removed.push_back(make_pair(events[i].y2, id));
		}
		
	}
	int res = 0;
	for(int i = 1; i <= N; i++){
		res += (touched[i] == false);
	}
	printf("%d\n", res);
}
int main(){
	cin>>N;
	for(int i = 1; i <= N; i++){
		scanf("%d%d%d%d", x1+i, y1+i, x2+i, y2+i);
	}
	solve();
	return 0;
}
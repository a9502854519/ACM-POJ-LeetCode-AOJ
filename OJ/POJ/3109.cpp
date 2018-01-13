#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
#define MAX_N 100000

using namespace std;
struct Data{
	int x;
	int y;
	bool operator < (const Data& other){
		return y < other.y || ( y == other.y && x < other.x);
	}
};
Data d[MAX_N];
int N;
int bit[MAX_N+1];
int visited[MAX_N+1];
int s[MAX_N+1];

int sum(int i){
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}

void add(int i, int x){
	while(i <= N){
		bit[i] += x;
		i += i & -i;
	}
}

void compress(Data* d){
	vector<int> xs;
	vector<int> ys;
	
	for(int i = 0; i < N; i++){
		xs.push_back(d[i].x);
		ys.push_back(d[i].y);
	}
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	for(int i = 0; i < N; i++){
		d[i].x = 1 + (lower_bound(xs.begin(), xs.end(), d[i].x) - xs.begin());
		d[i].y = 1 + (lower_bound(ys.begin(), ys.end(), d[i].y) - ys.begin());
	}
}
int main(){
	cin>>N;
	for(int i = 0; i < N; i++) scanf("%d %d\n", &d[i].x, &d[i].y);
	//®y¼ÐÀ£ÁY
	compress(d);
	//BIT
	sort(d, d+N);
	memset(bit, 0, sizeof(bit));
	memset(visited, 0, sizeof(visited));
	memset(s, 0 , sizeof(s));
	int result = N;
	for(int i = 0; i < N; i++){
		int x = d[i].x, y = d[i].y;
		if(visited[x]){
			int t = sum(x);
			result += t - s[x];
			s[x] = t;
		}else{
			visited[x] = true;
			int temp = sum(x);
			add(x, -temp);
			add(x+1, temp);
		}
		if(y == d[i+1].y){
			add(x+1, 1);
			add(d[i+1].x, -1);
		}
	}
	cout<<result<<endl;
	return 0;
}
			
	
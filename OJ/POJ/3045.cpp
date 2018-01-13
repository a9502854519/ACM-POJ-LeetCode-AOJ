#include<iostream>
#include<algorithm>
#define INF 1E9

using namespace std;

struct cow{
	int w;
	int s;
	bool operator < (cow& other){
		return w+s < other.w+other.s;
	}
};
cow Cow[50000];
int main(){
	int N,total = 0,risk;
	cin>>N;
	for(int i = 0; i < N; i++){
		cin>>Cow[i].w>>Cow[i].s;
		total += Cow[i].w;
	}
	sort(Cow, Cow+N);
	risk  = -INF;
	for(int i = N-1; i >= 0; i--){
		total -=Cow[i].w;
		risk = max(risk, total - Cow[i].s);
	}
	cout<<risk<<endl;
	
}
	
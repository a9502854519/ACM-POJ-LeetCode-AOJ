#include<iostream>
#include<cstdio>
#include<algorithm>
#define INF 1.0E9
using namespace std;



int main(){
	int N, S, min_cost,Ci,Yi;
	unsigned long long int total_cost;
	cin>>N>>S;

	min_cost = INF;
	total_cost  = 0;
	for(int i=0;i<N;i++){
		cin>>Ci>>Yi;
		min_cost = min(min_cost, Ci);
		total_cost+=min_cost*Yi;
		min_cost += S;
	}
	cout<<total_cost<<endl;
	
	return 0;
}

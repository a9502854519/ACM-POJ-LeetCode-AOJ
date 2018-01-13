#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<algorithm>
#define INF 1E9

using namespace std;



int relation[301];
int d[301][301];

int main(){
	int N,M,a,b,sum,ct,res;
	cin>>N>>M;
	for(int i=1;i<=N;i++){
		fill(d[i], d[i]+N+1, INF);
	}
	for(int i=0;i<M;i++){
		cin>>a;
		for(int j=1;j<=a;j++){
			cin>>relation[j];
			d[relation[j]][relation[j]] = 0;
			for(int k=j-1;k>=1;k--){
				d[relation[k]][relation[j]] = 1;
				d[relation[j]][relation[k]] = 1;
			}
			
		}
	}
	for(int k = 1;k<=N;k++){
		for(int i = 1;i<=N;i++){
			for(int j = 1;j<=N;j++){
				d[i][j] = min(d[i][j] , d[i][k] + d[k][j]);
			}
		}
	}
	res = INF, ct = 0;
	for(int i = 1;i<=N;i++){
		sum = 0;
		for(int j = 1;j<=N;j++){
			if(d[i][j] < INF){
				sum += d[i][j];
			}
		}
		res = min(res, sum);
	}
	cout<<res*100/(N-1)<<endl;
	return 0;
}
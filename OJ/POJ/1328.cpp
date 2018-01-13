#include<iostream>
#include<cstdio>
#include<utility>
#include<algorithm>
#include<stack>
#include<cmath>
#define EPS 1.0E-3
using namespace std;

pair<int, int> rador[2000];
pair<double, double> interval[2000];
bool cmp(const pair<double, double>&p, const pair<double,double>& q){
	return p.first<q.first;
}
int main(){
	int n,d,res;
	double offset, left, right;
	stack<double> q;
	for(int ct=1;;ct++){
		cin>>n>>d;
		if(n==0) break;
		for(int i=0;i<n;i++){
			cin>>rador[i].first>>rador[i].second;
			if(rador[i].second <0 || rador[i].second > d) d = -1;
			if(d > 0){
				offset = sqrt(d*d - rador[i].second*rador[i].second);
			    interval[i] = make_pair(rador[i].first - offset, rador[i].first + offset);
			}
		}			
		sort(interval, interval+n,cmp);
		res = -1;	
		if(d > 0){
			res = 0;
			for(int i=0;i<n;i++){
				right = interval[i].second;
				left = interval[i].first ;
				if(q.empty()){
					q.push(right);
					res++;
				}else if(right < q.top() || abs(right - q.top()) < EPS){
					q.pop();
					q.push(right);
				}else if (left > q.top() && abs(left - q.top()) > EPS){
					q.pop();
					q.push(right);
					res++;
				}
			}
			while(!q.empty()) q.pop();
		}
		printf("Case %d: %d\n",ct, res);
		
	}
	return 0;
}
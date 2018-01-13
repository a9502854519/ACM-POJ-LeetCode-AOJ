#include<iostream>
#include<vector>
#include<cmath>
#include<cstdio>
#include<utility>
#include<algorithm>
#define INF 1000000001
using namespace std;

int main(){
	int n, k;
	vector< pair<int, int> > sum;
	while(cin>>n>>k){
		if(n == 0) break;
		sum.clear();
		sum.push_back(make_pair(0,0));
		for(int i = 1; i <= n; i++){
			pair<int, int> a;
			cin>>a.first;
			a.first += sum[i-1].first;
			a.second = i;
			sum.push_back(a);
		}

		sort(sum.begin(), sum.end());
		/*for(int i = sum.size() - 1; i >= 0; i--){
			printf("%d: %d\n",sum[i].second, sum[i].first);
		}
		cout<<endl;*/
		for(int i = 0; i < k; i++){
			int goal;
			scanf("%d", &goal);
			int gap = INF, l, u, res, temp;
			int s = 0, t = 1;
			while(t <= n){
				temp = sum[t].first - sum[s].first;
				temp = (sum[t].second < sum[s].second ? -temp : temp); 
				if(gap > abs( abs(temp) - goal )){
					gap = abs( abs(temp) - goal );
					res = temp;
					l = sum[s].second; u = sum[t].second;
					//printf("s = %d  t = %d  res = %d\n",s ,t ,res);
				}
				
				if(abs(temp) > goal && s < t-1) s++;
				else t++;
			}
			printf("%d %d %d\n",abs(res) , min(l, u)+1, max(l, u));
			
		}
	}
	return 0;
}
				
				
				
					
		
		
		
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

vector<int> prime;
void init(){
	prime.push_back(2);
	for(int i = 3; i <= 10000; i++){
		int j = 0;
		for(; j < prime.size(); j++){
			if(i % prime[j] == 0){
				break;
			}
		}
		if(j == prime.size()) prime.push_back(i);
		
	}
}
int main(){
	init();
	int n;
	while(cin>>n){
		if(n == 0) break;
		int s = 0, t = 1, sum = 2, count = 0;
		while(t < prime.size() && t - s > 0){
			if(sum < n) sum += prime[t++];
			else{
				if(sum == n) count ++;
				sum -= prime[s++];
			}
		}
		cout<<count<<endl;
	}
	return 0;
}
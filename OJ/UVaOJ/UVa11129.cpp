#include<iostream>
#include<vector>

using namespace std;

int n;
vector<int> p;

void solve(int i, int k){
	if(i + k > n - 1){
		p.push_back(i);
		return;
	}
	solve(i, 2*k);
	solve(i + k, 2*k);
}
		
int main(){
	while(cin>>n){
		if(n == 0) break;
		p.clear();
		solve(0,1);
		cout<<n<<": ";
		for(int i = 0; i < p.size(); i++) cout<<p[i]<<(i == n-1 ? "\n" : " ");
	}
	return 0;
}
	

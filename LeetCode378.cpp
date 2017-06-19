#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution {
public:
	vector<int> v;
	bool C(int x, int k){
		return upper_bound(v.begin(), v.end(), x) - v.begin() >= k;
	}
    int kthSmallest(vector<vector<int>>& matrix, int k) {
	    for(int i = 0; i < matrix.size(); i++){
			v.insert(v.end(), matrix[i].begin(), matrix[i].end());
		}
		sort(v.begin(), v.end());
		int ub = v[v.size()-1], lb = v[0] - 1, mid;//(lb, ub]
		while(ub - lb > 1){
			mid = (ub + lb)/2;
			if(C(mid, k)) ub = mid;
			else lb = mid;
		}
		return ub;
    }
};

int main(){
	vector< vector<int> > m;
	vector<int> temp;
	int n, t;
	cin>>n;
	for(int i = 0; i < n; i++){
		temp.clear();
		for(int j = 0; j < n; j++){
			cin>>t;
			temp.push_back(t);
		}
		m.push_back(temp);
	}
	Solution ans;
	cout<<ans.kthSmallest(m, 8)<<endl;
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#define MAX_W 10
#define INF 1E9

using namespace std;
typedef unsigned long long ull;

const ull B = 100000007;
int w, h; 
int s[MAX_W][MAX_W]; //可延伸的最大正方形邊長
int contain[MAX_W][MAX_W]; //有包含到這個元素的集合數量
bool same[MAX_W][MAX_W][MAX_W][MAX_W]; //兩個元素是否可以被同一個集合覆蓋到?
int limit;
int ct;

void init(vector<int>& f){
	memset(contain, 0, sizeof(contain));
	memset(same, false, sizeof(same));
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			s[i][j] = (f[i] >> (w - 1 - j)) & 1;
		}
	}
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			//計算每個元素往右下角可延伸的最長正方形邊長
			for(int k = 0;; k++){
				bool ok = true;
				if(i + k < h && j + k < w){
					for(int l = 0; ok && l <= k; l++){
						if(s[i + k][j + l] == 0 || s[i + l][j + k] == 0) ok = false;
					}
				}else{
					ok = false;
				}
				if(!ok){
					s[i][j] = k;
					break;
				}
			}
			//計算可包含到這個元素的集合數量
			for(int a = 0; a < s[i][j]; a++){
				for(int b = 0; b < s[i][j]; b++){
					contain[i + a][j + b]++;
				}
			}
			//計算可以被同個集合包含到的元素組合
			for(int a = 0; a < s[i][j] * s[i][j]; a++){
				int x1 = i + a / s[i][j], y1 = j + a % s[i][j];
				for(int b = 0; b < s[i][j] * s[i][j]; b++){
					int x2 = i + b / s[i][j], y2 = j + b % s[i][j];
					same[x1][y1][x2][y2] = same[x2][y2][x1][y1] = true;
				}
			}
		}
	}
}
int hstar(vector<int> f){
	//選取盡量多的點，其中每個集合最多只能有一個點被選中
	vector<P> ps, X;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if((f[i] >> (w - 1 - j)) & 1){
				ps.push_back(P(i, j, contain[i][j]));
			}
		}
	}
	sort(ps.begin(), ps.end());
	for(int i = 0; i < ps.size(); i++){
		bool ok = true;
		int x1 = ps[i].x, y1 = ps[i].y;
		for(int j = 0; j < X.size() && ok; j++){
			int x2 = X[j].x, y2 = X[j].y;
			if(same[x1][y1][x2][y2]) ok = false;
		}
		if(ok) X.push_back(ps[i]);
	}
	return X.size();
}
int dfs(int num, vector<int> f, int idx){
	if(num + hstar(f) > limit) return INF;
	
	ct++;
	vector<int> reset(f.begin(), f.end());
	for(; idx < w * h; idx++){
		int i = idx / w, j = idx % w;
		int k = s[i][j];
		if(k > 0){
			int tmp = ((1 << k) - 1) << (w - j - k), n = 0;
			for(int m = 0; m < k; m++){
				if((f[i + m] & (~tmp)) == f[i + m]) n++; //代表這一列所屬該集合的元素已經被選完
				f[i + m] &= ~tmp;
			}
			if(n < k){ //如果該集合還有元素沒被選到
				if(dfs(num + 1, f, idx + 1) < INF) return num;
			}
			for(int m = 0; m < k; m++) f[i + m] = reset[i + m];
			//如果這個元素沒有被任何集合包含到，那再往下找也沒意義
			//因為後面的集合無法覆蓋到這個元素，剪枝。
			if(((f[i] >> (w - 1 - j)) & 1) && n < k) break;
		}
	}	
	bool check = true;
	for(int i = 0; i < h && check; i++) check &= (f[i] == 0); //確認是否已經完成
	return (check ? num : INF);
}
int solve(vector<int>& f){
	init(f);
	ct = 0;
	for(limit = hstar(f);; limit++){
		if(dfs(0, f, 0) < INF) return limit;
	}
}
int main(){
	while(cin >> w >> h && (w || h)){
		vector<int> f(h, 0);
		for(int i = 0; i < h; i++){
			f[i] = 0;
			int a;
			for(int j = 0; j < w; j++){
				cin >> a;
				f[i] = (f[i] << 1) | a;
			}
		}
		cout << solve(f) << endl;
	}
	return 0;
}
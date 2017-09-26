#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 1000000000
using namespace std;

int N;
int data[75][75];
int bit[76][76];

int sum(int n, int i){
	int s = 0;
	while(i > 0){
		s += bit[n][i];
		i -= i & -i;
	}
	return s;
}
int sum(int n, int i, int j){
	n++, i++, j++;
	if(i <= j){
		return sum(n, j) - sum(n, i-1);
	}
	return sum(n, N) - sum(n, i - 1) + sum(n, j);
}

void add(int n, int i, int x){
	n++, i++;
	while(i <= N){
		bit[n][i]+=x;
		i += i & -i;
	}
}
void init(){
	memset(bit, 0, sizeof(bit));
}


int main(){
	int t;
	cin>>t;
	for(int a = 0; a < t; a++){
		init();
		cin>>N;
		
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				cin>>data[i][j];
				add(i, j, data[i][j]);
			}
		}
		int res = -INF;
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				int s = 0, rev = 0, total = 0;
				int t = 0;
				if(j != i-1){
					for(int k = 0; k < N; k++){
						int temp = sum(k, i, j);
						/*計算總和最小的區間，rev是區間總和最小的值*/
						total += temp;
						s += temp;
						rev = min(rev, s);
						if(s > 0) s = 0;
						/*計算總和最大的區間，res是區間總和最大的值*/
						t += temp;
						res = max(res, t);
						if(t < 0) t = 0;
					} 
					if(total != rev){//如果total == rev，則代表全部都是負數
						res = max(res, total - rev);
					}
				}
			}
		}
		cout<<res<<endl;
	}
	return 0;
}
			
				
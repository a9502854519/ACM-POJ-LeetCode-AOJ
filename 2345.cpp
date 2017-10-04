#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;
typedef vector<int> vec;
typedef vector<vec> mat;


void swap(vec& A, vec& B){
	vec t = A;
	A = B;
	B = t;
}
void solve(mat A){
	int n = A.size();
	for(int i = 0; i < n; i++) A[i][n] = 1;
	for(int i = 0; i < n; i++){//處理第i個未知數
		//把正在處理的未知數系數為1的換到第i行
		int pivot = i;
		for(int j = i; j < n; j++){
			if(A[j][i] == 1){
				pivot = j;
				break;
			}
		}
		swap(A[i], A[pivot]);
		//用第i行去消掉其它行的第i個未知數
		for(int j = 0; j < n; j++){
			if(i != j && A[j][i] == 1){
				for(int k = i; k <= n; k++) A[j][k] ^= A[i][k];
			}
		}		
	}
	for(int i = 0; i < n; i++){
		if(A[i][i] == 0 && A[i][n] == 1){
			printf("No solution\n");
			return;
		}
	}
	for(int i = 0; i < n; i++){
		if(A[i][i] == 1 && A[i][n] == 1){
			printf("%d ", i+1);
		}
	}	
	printf("\n");
}
	
int main(){
	int N;
	cin>>N;
	mat A(N, vec(N+1, 0));
	for(int i = 0; i < N; i++){
		int a;
		while(true){
			scanf("%d", &a);
			if(a == -1) break;
			A[a-1][i] = 1;
		}
	}
	solve(A);
}
		
		
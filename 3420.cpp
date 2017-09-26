#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>

using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int N, M;
mat mul(mat& A, mat& B){
	mat C(A.size(), vec(B[0].size()));
	for(int i = 0; i < A.size(); i++){
		for(int j = 0; j < B[0].size(); j++){
			for(int k = 0; k < B.size(); k++){
				C[i][j] = (C[i][j] + A[i][k]*B[k][j]) % M;
			}
		}
	}
	return C;
}
mat pow(mat &A, int n){
	mat B(A.size(), vec(A.size()));
	for(int i = 0; i < A.size(); i++){
		B[i][i] = 1;
	}
	while(n > 0){
		if(n & 1) B = mul(B, A);
		A = mul(A, A);
		n >>= 1;
	}
	return B;
}
int main(){
	int A1[5][5] = {{1,1,0,1,4},{0,1,0,0,2},{0,0,0,1,1},{0,0,1,0,0},{1,0,0,0,0}};
	int B1[5][1] = {{1},{0},{0},{0},{1}};
	mat A(5, vec(5));
	mat B(5, vec(1));
	
	while(cin>>N>>M){
		if(N == 0 && M == 0) break;
		for(int i = 0; i < 5; i++){
			A[i].assign(A1[i], A1[i]+5);
			B[i][0] = B1[i][0];
		}
		A = pow(A, N-1);
		A = mul(A, B);
		cout<<A[0][0]<<endl;
	}
	return 0;
}
		
#include<iostream>
#include<iomanip>
#include<ctime>
#include<cstdio>
#define MAX_N 1000
#define MAX_M 500
#define MAX_T 20
using namespace std;

int main(){
	int N, M, T;
	N = rand() % MAX_N + 1;
	M = rand() % MAX_M + 1;
	T = rand() % MAX_T + 1;
	while(T--){
		for(int i = 0; i < N; i++){
			printf("chen ");
			int C = rand() % M + 1;
			while(C--){
				printf("%d ", rand() % M);
			}
			printf("\n");
		}
	}
	printf("0 0\n");
	return 0;
}


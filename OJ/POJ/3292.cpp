#include<iostream>
#include<algorithm>
#define MAX 250000

using namespace std;

int H_Prime[MAX + 1];//0 means it is not a H-prime, 1 means is has been checked as a H-prime, 2 means it is a H-semiprime
int ct[MAX+1];
void init(){
	fill(H_Prime, H_Prime + 1 + MAX, 1);
	H_Prime[0] = 0;
	H_Prime[1] = 1;
	//先打質數表
	for(long long int i = 1; i<=MAX; i++){
		if(H_Prime[i] == 1){
			for(long long int j = i;;j++){
				long long int n = (4*i*j + i + j);
				if(n > MAX) break;
				H_Prime[n] = 0;
			}
		}
	}
	//再打semiprime
	for(long long int i = 1;i<=MAX; i++){
		if(H_Prime[i] == 1){
			for(long long int j = i;;j++){
				long long int n = 4*i*j + i + j;
				if(n > MAX) 
					break;
				if(H_Prime[j] == 1){
					H_Prime[n] = 2;
				}
			}
		}
	}
	//老子就不信這樣不能過，操你媽的Nibali				
	ct[0] = 0;
	for(int i = 1; i<=MAX; i++){
		ct[i] = ct[i-1];
		if(H_Prime[i] == 2) ct[i] ++;
	}
}
int main(){
	int h;
	init();
	while(cin>>h){
		if(h == 0) break;
		cout<<h<<" ";
		h = (h - 1)/4;
		cout<<ct[h]<<endl;
	}
	return 0;
}
		
		
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>

#define MAX_N 50001
#define MAX_n 50000
using namespace std;

int n, N;
int bit[MAX_N+1];//1~50001


struct Data{
	int a;
	int b;
	int c;
	bool operator < (const Data& other){
		return b < other.b;
	}
}data[MAX_n];

int sum(int i){
	int s = 0;
	while(i > 0){
		s += bit[i];
		i -= i & -i;
	}
	return s;
}
int sum(int i, int j){
	return sum(j) - sum(i-1);
}
bool add(int i, int v){
	if(sum(i, i) == 1) return false; 
	while(i <= N){
		bit[i] += v;
		i += i & -i;
	}
	return true;
}
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d%d%d", &data[i].a, &data[i].b, &data[i].c);
		data[i].a++; data[i].b++;
	}

	sort(data, data+n);
	N = data[n-1].b;//bit的範圍
	memset(bit, 0, sizeof(bit));
	int res = 0;
	for(int i = 0; i < n; i++){
		int a = data[i].a, b = data[i].b, c = data[i].c;
		int s = c - sum(a, b);
		//if(i < 50) printf("%5d %5d %5d\ts = %4d   sum() = %4d\n",a,b,c,s,c-s);
		if(s > 0){
			res += s;
			for(int j = b; s > 0; j--){
				if(add(j, 1)) s--;
			}
		}
	}

	printf("%d\n", res);
			
	return 0;
}
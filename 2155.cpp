#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 1000

using namespace std;

int bit0[MAX_N+1][MAX_N+1];
int N;

int sum(int bit[][MAX_N+1], int i, int j){
	int s = 0;
	for(int y = j; y > 0; y -= y & -y){
		for(int x = i; x > 0; x -= x & -x){
			s += bit[x][y];
		}
	}
	return s;
}
void add(int bit[][MAX_N+1], int i, int j, int v){
	for(int y = j; y <= N; y += y & -y){
		for(int x = i; x <= N; x += x & -x){
			bit[x][y] += v;
		}
	}
}


int main(){
	int X;
	cin>>X;
	while(X--){
		int T;
		scanf("%d%d", &N, &T);
		memset(bit0, 0, sizeof(bit0));
		char c;
		int x1,y1,x2,y2;
		while(T--){
			scanf(" %c",&c);
			if(c == 'Q'){
				scanf("%d%d",&x1, &y1);
				int res = sum(bit0, x1, y1);
				printf("%d\n", res & 1);
			}else{
				scanf("%d%d%d%d",&x1, &y1, &x2, &y2);	
				add(bit0, x1, y1, 1);
				add(bit0, x2+1, y1, -1);
				add(bit0, x1, y2+1, -1);
				add(bit0, x2+1, y2+1, 1);
			}		
			
		}
		printf("\n");
		
	}
	return 0;
}
			
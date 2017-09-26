#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 50000
#define INF 1E7

using namespace std;

struct Data{
	int mn;
	int mx;
};

int N;
int height[MAX_N];
Data dat[4*MAX_N + 1];

Data init(int k, int a, int b){
	Data d, d1, d2;
	if(b - a == 1){
		d.mn = height[a];
		d.mx = height[a];
		dat[k] = d;
		return d;
	}
	d1 = init(2*k+1, a, (a+b)/2);
	d2 = init(2*k+2, (a+b)/2, b);
	d.mn = min(d1.mn, d2.mn);
	d.mx = max(d1.mx, d2.mx);
	dat[k] = d;
	return d;
}
Data query(int a, int b, int k, int l, int r){
	if(b <= l || a >= r){
		Data d;
		d.mn = INF, d.mx = -INF;
		return d;
	}
	if(a <= l && b >= r){
		return dat[k];
	}else{
		Data d, d1, d2;
		d1 = query(a, b, 2*k+1, l, (l+r)/2);
		d2 = query(a, b, 2*k+2, (l+r)/2, r);
		d.mn = min(d1.mn, d2.mn);
		d.mx = max(d1.mx, d2.mx);
		return d;
	}
}
int main(){
	int Q;
	scanf("%d%d", &N, &Q);
	for(int i = 0; i < N; i++){
		scanf("%d", height+i);
	}
	init(0, 0, N);
	for(int i = 0; i < Q; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		Data d = query(a-1, b, 0, 0, N);
		printf("%d\n", d.mx - d.mn);
	}
	return 0;
}


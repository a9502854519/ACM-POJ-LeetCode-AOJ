#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

int n;
int *dat, *heights;

int max(int a, int b){
	return a < b ? b : a;
}
void update(int x, int v){
	int k = x + n - 1;
	dat[k] = x;
	while(k > 0){
		k = (k - 1) / 2;
		if(dat[2 * k + 1] < 0 || dat[2 * k + 2] < 0) dat[k] = max(dat[2 * k + 1], dat[2 * k + 2]);
		else if(heights[ dat[2 * k + 1] ] < heights[ dat[2 * k + 2] ]) dat[k] = dat[2 * k + 1];
		else dat[k] = dat[2 * k + 2];
	}
}
void init(int n_){
	n = 1;
	while(n < n_) n *= 2;

	dat = new int[2 * n - 1];
	//dat = malloc((2 * n - 1) * sizeof(int))
	memset(dat, -1, sizeof(dat));
	for(int i = 0; i < n_; i++){
		update(i, heights[i]);
	}
}
int query(int a, int b, int k, int l, int r){
	if(a >= r || b <= l) return -1;
	if(a <= l && b >= r) return dat[k];

	int v1 = query(a, b, 2 * k + 1, l, (l + r) / 2);
	int v2 = query(a, b, 2 * k + 2, (l + r) / 2, r);

	if(v1 < 0 || v2 < 0) return max(v1, v2);
	else if(heights[v1] < heights[v2]) return v1;
	else return v2;
}
int calc(int a, int b){
	if(b - a <= 1){
		return heights[a] * (b - a);
	}

	int x = query(a, b, 0, 0, n);
	int v1 = (b - a) * heights[x];
	int v2 = calc(a, x);
	int v3 = calc(x + 1, b);
	return max(max(v1, v2), v3);
}
int largestRectangleArea(int* h, int heightsSize) {
	if(heightsSize == 0) return 0;
	heights = h;
	init(heightsSize);		
	return calc(0, heightsSize);
}

int main(){
	int  heightsSize;
	scanf("%d", &heightsSize);
	int h[heightsSize];
	for(int i = 0; i < heightsSize; i++){
		scanf("%d", h+i);
	}
	printf("%d\n", largestRectangleArea(h, heightsSize));
	return 0;
}

#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 100000

using namespace std;

struct Data{
	int frq;
	int val;
};
int n;
Data dat[3*MAX_N+1];
int a[MAX_N];

Data init(int k, int l, int r){
	Data d, d1, d2;
	if(r - l == 1){
		d.frq = 1;
		d.val = a[l];
		dat[k] = d;
		return d;
	}
	d1 = init(2*k+1, l, (l+r)/2);
	d2 = init(2*k+2, (l+r)/2, r);
	if(d1.val == d2.val){
		d.frq = d1.frq + d2.frq;
		d.val = d1.val;
		dat[k] = d;
	}else{
		d.frq = max(d1.frq, d2.frq);
		d.val = (d1.frq > d2.frq ? d1.val : d2.val);
		
		int count = 0;
		for(int i = (l+r)/2; a[i] == a[i-1] && i < r; i++) count++;
		for(int i = (l+r)/2-1; a[i] == a[i+1] && i >= l; i--) count++;
		d.frq = max(count, d.frq);
		d.val = (d.frq > count ? d.val : a[(l+r)/2]);
		dat[k] = d;
	}
	return dat[k];
}
Data query(int i, int j, int k, int l, int r){
	
	Data d, d1, d2;
	if(i >= r || j <= l){
	    d.frq = 0;
		d.val = 0;
		return d;
	}
	if(i <= l && j >= r){
		return dat[k];
	}
	d1 = query(i, j, 2*k+1, l, (l+r)/2);
	d2 = query(i, j, 2*k+2, (l+r)/2, r);
	if(d1.val == d2.val){
		d.frq = d1.frq + d2.frq;
		d.val = d1.val;
	}else{
		d.frq = max(d1.frq, d2.frq);
		d.val = (d1.frq > d2.frq ? d1.val : d2.val);
		if(d1.frq != 0 && d2.frq != 0){
			int count = 0;
			for(int c = (l+r)/2; a[c] == a[c-1] && c < min(j, r); c++) count++;
			for(int c = (l+r)/2-1; a[c] == a[c+1] && c >= max(i, l); c--) count++;
			d.frq = max(count, d.frq);
			d.val = (d.frq > count ? d.val : a[(l+r)/2]);
		}
	}
	return d;
}
int main(){
    int q;
	
	while(cin>>n){
		if(n == 0) break;
		cin>>q;
		for(int i = 0; i < n; i++){
			scanf("%d", a+i);
		}
		init(0, 0, n);
		//printf("%d\n", query(4, 10, 0, 0, n).frq);
		for(int i = 0; i < q; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			x--;
			Data d = query(x, y, 0, 0, n);
			printf("%d\n", d.frq);
		}
	}
	return 0;
}
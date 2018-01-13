#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define INF 1E10
using namespace std;
int gcd(int a, int b){
	int c;
	while(b){
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}
int main(){
	string s;
	int n, d, res_a, res_b ;
	while(cin>>s){
		if(s == "0") break;
		n = s.size();
		d = 0;
		for(int i = 2;i < n-3; i++){
			d = d*10 + (int)(s[i] - '0');
		}
		n-=5;
		int b, a, g;
		res_b = INF;
		for(int i = 1; i<=n;i++){
			b = 0;
			for(int j = 0; j < i;j++){
				b = b * 10 + 9;
			}
			for(int j = 0; j < n - i; j++){
				b = b * 10;
			}
			
			a = d - (int)(d / pow(10, i));
			g = gcd(a, b);
			
			if(res_b > b / g){
				res_a = a / g;
				res_b = b / g;
			}
		}
		cout<<res_a<<"/"<<res_b<<endl;
	}
	return 0;
}
	

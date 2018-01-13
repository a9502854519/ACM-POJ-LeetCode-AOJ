#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#define INF 1E9

using namespace std;
typedef long long int ll;

ll clothes[100000];
ll n,k;//有n件衣服，烘乾機可以在一分鐘內排乾K單位的水

inline ll myceil(ll a, ll b){
	return a/b + (a%b>0 ? 1 : 0);
}


bool C(ll limit){
	ll sum = 0, temp;
	for(ll i = 0; i < n; i++){
		if(clothes[i] > limit){
			//在限制內，盡可能減少烘乾機的使用時數。
			sum += myceil(clothes[i] - limit, k - 1);
		}
		if(sum > limit) return false;
	}
	return true;
}

int main(){
	
	ll lb = 1, ub = 0, mid;	
	scanf("%lld",&n);
	for(ll i = 0; i<n;i++){
		scanf("%lld",&clothes[i]);
		ub = max(ub, clothes[i]);
	}
	scanf("%lld",&k);
	if(k != 1){
		while(ub - lb > 0){
			mid = (ub + lb) / 2;
			
			if(C(mid)) ub = mid;
			else lb = mid+1;
		}
	}
	
	cout<<ub<<endl;
	
	return 0;
}
		
	
	
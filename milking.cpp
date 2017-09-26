#include<iostream>
#include<algorithm>
using namespace std;
struct Farmer_John{
	int start;
	int end;
	int eff;
};
Farmer_John Fj[1000];
int calc[1000];
int dp[1000];
void swap(int i, int j){
	Farmer_John temp = *(Fj+i);
	*(Fj+i) = *(Fj+j);
	*(Fj+j) =temp;
	calc[i] = (Fj+i)->end;
	calc[j] = (Fj+j)->end;
}
void sort(int left,int right){
	if(left<right){
		int i = left, j= right+1, pivot = Fj[left].end;
		do{
			do i++; while(Fj[i].end < pivot);
			do j--; while(Fj[j].end > pivot);
			if(i<j) swap(i,j);
		}while(i<j);
		swap(left,j);
		sort(left,j-1);
		sort(j+1,right);
	}
}
		
int main(){
	int N,M,R,res,j;
	cin>>N>>M>>R;
	for(int i=0;i<M;i++){
		cin>>Fj[i].start>>Fj[i].end>>Fj[i].eff;
		Fj[i].end+=R;
	}
	sort(0,M-1);
	dp[0] = Fj[0].eff;
	res = dp[0];
	for(int i=1; i<M;i++){
		dp[i] = Fj[i].eff;
		j = upper_bound(calc,calc+M,Fj[i].start)-calc-1;
		for(;j>=0; j--){
			if(Fj[i].eff + dp[j] > dp[i]){
				dp[i] = Fj[i].eff+dp[j];
		}
		res = max(res,dp[i]);
	}
	cout<<res<<endl;
	return 0;
}
	
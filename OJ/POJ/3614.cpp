#include<iostream>
#include<algorithm>
#include<queue>
#include<utility>
using namespace std;

pair<int, int> Cow,Lotion[2500];
priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > a;
int main(){
	//1<=C<=2500 :牛的數量
	//1<=L<=2500 :防曬乳的數量
	int C,L,res,minSPF,maxSPF;
	cin>>C>>L;
	for(int i=0;i<C;i++){
		cin>>Cow.second>>Cow.first;
		a.push(Cow);
		//second是下限，first是上限
	}
	for(int i=0;i<L;i++){
		cin>>Lotion[i].first>>Lotion[i].second;
		//first是乳液的SPF，second是cover
	}
	sort(Lotion,Lotion+L);
	res = 0;
	while(!a.empty()){
		minSPF = a.top().second;
		maxSPF = a.top().first;
		a.pop();
		for(int i=0;i<L;i++){
			if(Lotion[i].second > 0 && minSPF<=Lotion[i].first && Lotion[i].first<=maxSPF){
				res++;
				Lotion[i].second--;
				break;
			}
		}
	}
	cout<<res<<endl;	
	return 0;
}
	
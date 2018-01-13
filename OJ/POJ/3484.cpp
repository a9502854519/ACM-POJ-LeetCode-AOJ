#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>

using namespace std;

struct Data{
	long long int x,y,z;
};
vector<Data> v;
long long int ub,lb,mid,res;

int ceil(int y, int x){
	return y/x + (y%x > 0);
}

bool C(long long int x){
	long long int count = 0, left, right;
	for(int i = 0; i < v.size(); i++){
		left = max(v[i].x, lb+1);
		right = min(v[i].y, x);
		if(left <= right){
			//printf("%lld %lld\n",left, right);
			left = ceil(left - v[i].x, v[i].z);
			right = (right - v[i].x)/v[i].z;
			count += (right - left) + 1;
		}
	}
	//cout<<count<<endl;
	res = (count % 2 == 1 ? count : res);
	return count % 2 == 1;	
}
int main(){
	char buff[40];
	Data data;
	bool end = false;
	while(!end){
		v.clear();
		ub = -2147583649;
		lb = 2147583648;
		while(true){
			if(fgets(buff, sizeof(buff), stdin) == NULL){
				end = true;
				break;
			}
			else if(buff[0] == '\n') break;
			else{
				sscanf(buff, "%lld %lld %lld", &data.x, &data.y, &data.z);
				v.push_back(data);
				ub = max(ub, data.y);
				lb = min(lb, data.x);
			}
		}
		if(v.size() > 0){
			ub++;
			long long int no_corrupt = ub;
			lb--;
			while(ub - lb > 1){
				mid = (ub + lb) / 2;
				if(C(mid)) ub = mid;
				else lb = mid;
			}
			if(ub == no_corrupt) printf("no corruption\n");
			else{
				C(ub);
				printf("%lld %lld\n",ub, res);
			}
			
		}
	}
	return 0;
}
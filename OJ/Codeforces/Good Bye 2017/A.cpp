#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

string s;

int solve(){
	int res = 0;
	for(int i = 0; i < s.size(); i++){
		if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
			res++;
		}
		else if(s[i] - '0' < 10 && (s[i] - '0') % 2 == 1){
			res++;
		}
	}
	return res;
}
int main(){
	cin>>s;
	cout << solve() << endl;
	return 0;
}
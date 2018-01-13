#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define INF 1E9

using namespace std;
typedef unsigned long long ull;

string s[3];
const int N = 3;
const ull B = 100000007;

bool cmp(const string& a, const string& b){
	return a.length() > b.length();
}
bool contain(string a, string b){
	int al = a.length(), bl = b.length();

	ull t = 1;
	for(int i = 0; i < bl; i++) t *= B;

	ull ah = 0, bh = 0;
	for(int i = 0; i < bl; i++){
		ah = ah * B + a[i];
		bh = bh * B + b[i];
	}
	for(int i = 0; i + bl <= al; i++){
		if(ah == bh) return true;
		if(i + bl < al){
			ah = ah * B + a[i + bl] - a[i] * t;
		}
	}
	return false;
}
int max_overlap(string a, string b){
	int al = a.length(), bl = b.length();
	
	ull ah = 0, bh = 0, t = 1;
	int tmp = 0;
	for(int i = 0; i <= min(al, bl); i++){
		if(ah == bh) tmp = max(tmp, i);
		if(i < min(al, bl)){
			bh = bh * B + b[i];
			ah = ah + t * a[al - i - 1];
			t *= B;
		}
	}
	return tmp;
}


int solve(){
	sort(s, s + N, cmp);	
	vector<string> str;
	str.push_back(s[0]);
	if(!contain(s[0], s[1])) str.push_back(s[1]);
	if(!contain(s[0], s[2]) && !contain(s[1], s[2])) str.push_back(s[2]);

	
	int N = str.size(), res = INF;
	int p[N];
	for(int i = 0; i < N; i++) p[i] = i;
	do{
		int tmp = str[p[0]].length();
		for(int i = 0; i + 1 < N; i++){
			tmp += str[p[i + 1]].length() - max_overlap(str[p[i]], str[p[i + 1]]);
		}
		res = min(res, tmp);
	}while(next_permutation(p, p + N));
	return res;
}
int main(){
	cin>>s[0]>>s[1]>>s[2];
	printf("%d\n", solve());
	return 0;
}

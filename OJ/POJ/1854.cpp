#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 8000

using namespace std;

int n;
char str[MAX_N + 1];

int solve(char *s, int length){
	if(length <= 1) return 0;
	
	/*for(int i = 0; i < length; i++){
		printf("%c", s[i]);
	}
	cout<<endl;*/
	
	int res;
	for(int i = 0; i + 1 < length; i++){
		if(s[i] == s[length - 1]){
			for(int j = i; j > 0; j--) s[j] = s[j - 1];
			s[0] = s[length - 1];
			res = i;
			break;
		}else if(s[0] == s[length - 1 - i]){
			for(int j = length - 1 - i; j + 1 < length; j++) s[j] = s[j + 1];
			s[length - 1] = s[0];
			res = i;
			break;
		}
		
	}
	if(s[0] == s[length - 1]){
		int temp = solve(s + 1, length - 2);
		if(temp >= 0) return res + temp;
	}
	return -1;	
}
int main(){
	int c;
	scanf("%d\n", &c);
	while(c--){
		scanf("%s\n", str);
		int temp;
		if((temp = solve(str, strlen(str))) < 0) printf("Impossible\n");
		else printf("%d\n", temp);
	}
	return 0;
}
	
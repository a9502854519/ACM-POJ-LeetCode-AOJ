#include<iostream>
#include<cstdio>


using namespace std;

const int n = 4;
int table[n][n];
int state;
bool check(int c){
/*	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%2d ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
*/
	bool ok;

	ok = true;
	for(int i = 0; i < n; i++){
		if(table[i][i] != c) ok = false;
	}
	if(ok) return true;

	ok = true;
	for(int i = 0; i < n; i++){
		if(table[n-i-1][i] != c) ok = false;
	}
	if(ok) return true;

	for(int j = 0; j < n; j++){
		ok = true;
		for(int i = 0; i < n; i++){
			if(table[j][i] != c) ok = false;
		}
		if(ok) return true;	
	}

	for(int j = 0; j < n; j++){
		ok = true;
		for(int i = 0; i < n; i++){
			if(table[i][j] != c) ok = false;
		}
		if(ok) return true;
	}
	return false;
}
//false : 沒人贏得了
//true  : 還有機會
bool hope(){
	int count = 0;

	bool zero = false, one = false;
	for(int i = 0; i < n; i++){
		zero |= (table[i][i] == 0);
		one  |= (table[i][i] == 1);
	}
	count += (zero && one);

	zero  = false, one = false;
	for(int i = 0; i < n; i++){
		zero |= (table[n-i-1][i] == 0);
		one  |= (table[n-i-1][i] == 1);
	}
	count += (zero && one);

	for(int j = 0; j < n; j++){
		zero = false, one = false;
		for(int i = 0; i < n; i++){
			zero |= (table[j][i] == 0);
			one  |= (table[j][i] == 1);
		}
		count += (zero && one);
	}

	for(int j = 0; j < n; j++){
		zero = false, one = false;
		for(int i = 0; i < n; i++){
			zero |= (table[i][j] == 0);
			one  |= (table[i][j] == 1);
		}
		count += (zero && one);
	}
	return count < 10;
}
// -1 和局
// 0  輸
// 1  贏

int dfs(int c){
	state++;
	if(!hope()) return -1;

	int ok = 0;
	bool update = false;
	int result;

	for(int i = 0; i < n; i++){
		for(int j = 0 ; j < n; j++){
			if(table[i][j] == -1){
				update = true;
				table[i][j] = c;
				
				if(check(c) || (result = dfs(c ^ 1)) == 0){
					ok = 1;
				}

				table[i][j] = -1;
				if(ok == 1) return 1;
				if(result == -1) ok = -1;

			}	
		}
	}
	if(!update) return -1;
	return ok;
}
void solve(){
/*	printf("solve : \n");
	for(int i = 0; i < n; i++){
		for(int j = 0 ; j < n; j++){
			printf("%2d ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
*/	state = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(table[i][j] == -1){
				table[i][j] = 1;

				printf("%d %d\n", i, j);
				if(check(1) || dfs(0) == 0){
					printf("(%d,%d)\n", i, j);
					return;
				}
				table[i][j] = -1;
			}
		}
	}
	cout<<state<<endl;
	printf("#####\n");
}
int main(){
	char c;
	while(cin>>c){
		if(c == '$') break;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				cin>>c;
				if(c == 'x') table[i][j] = 1;
				else if(c == 'o') table[i][j] = 0;
				else  table[i][j] = -1;
			}
		}
		solve();
	}
	return 0;
}


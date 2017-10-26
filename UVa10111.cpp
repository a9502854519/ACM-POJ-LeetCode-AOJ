#include<iostream>
#include<cstdio>


using namespace std;

const int n = 4;
int table[n][n];
int limit[2];
int m;

struct P{
	int position[2];
	P () {}
	P (int a, int b){
		position[0] = a, position[1] = b;
	}
};
bool check(int c){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%2d ", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");

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
bool count(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(table[i][j] == -1) return false;
		}
	}
	return true;
}



// -2 狀態重複
// -1 和局
// 0  輸
// 1  贏

int dfs(int c, P last){
	int ok = 0;
	bool update = false;
	int result;

	for(int k = last.position[c] + 1; k < n * n; k++){
		int i = k / n, j = k % n;

		if(table[i][j] == -1){
			update = true;
			table[i][j] = c;
			last.position[c] = k;

			if(check(c) || (result = dfs(c ^ 1, last)) == 0){
				ok = 1;
			}

			table[i][j] = -1;
			if(ok == 1) return 1;
			if(result == -1) ok = -1;

		}
	}
	if(!update){
		if(count()) return -1;
		return -2;
	}
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
*/	
	P last(-1, -1);	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(table[i][j] == -1){
				table[i][j] = 1;
				last.position[1] = i * n + j;

				cout<<"               restart\n";
				if(check(1) || dfs(0, last) == 0){
					printf("(%d,%d)\n", i, j);
					return;
				}
				table[i][j] = -1;
			}
		}
	}
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


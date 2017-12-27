#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define MAX_W 1000
#define MAX_P 100

using namespace std;
typedef unsigned long long int ull;

int mat[MAX_W][MAX_W];
int pattern[MAX_W][MAX_W], tmp[MAX_W][MAX_W];
int w, h, p;
int cv[123];
ull hash[MAX_W][MAX_W];

void move(){
	for(int i = 0; i < p; i++){
		for(int j = 0; j < p; j++){
			pattern[i][j] = tmp[i][j];
		}
	}
}
void rotate(){
	for(int i = 0; i < p; i++){
		for(int j = 0; j < p; j++){
			tmp[j][p - 1 - i] = pattern[i][j];
		}
	}
	move();
}
void mirror(){
	for(int i = 0; i < p; i++){
		for(int j = 0; j < p; j++){
			tmp[i][p - 1 - j] = pattern[i][j];
		}
	}
	move();
}
void compute_hash(int a[MAX_W][MAX_W], int n, int m){
	const ull B1 = 9973;
	const ull B2 = 100000007;

	ull t1 = 1, t2 = 1;
	for(int i = 0; i < p; i++){
	       	t1 *= B1;
		t2 *= B2;
	}

	for(int i = 0; i < n; i++){
		ull e = 0;
		for(int j = 0; j < p; j++) e = e * B1 + a[i][j];

		for(int j = 0; j + p <= m; j++){
			tmp[i][j] = e;
			if(j + p < m) e = e * B1 + a[i][j + p] - a[i][j] * t1;
		}
	}

	for(int j = 0; j + p <= m; j++){
		ull e = 0;
		for(int i = 0; i < p; i++){
			e = e * B2 + tmp[i][j];
		}

		for(int i = 0; i + p <= n; i++){
			hash[i][j] = e;
			if(i + p < n) e = e * B2 + tmp[i + p][j] - tmp[i][j] * t2;
		}
	}
}
int solve(){
	set<ull> s;	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 4; j++){
			/***
			for(int a = 0; a < p; a++){
				for(int b = 0; b < p; b++){
					cout<<pattern[a][b];
				}
				cout<<endl;
			}
			cout<<endl;
			/***/
			compute_hash(pattern, p, p);
			s.insert(hash[0][0]);
			rotate();
		}
		mirror();
	}
	compute_hash(mat, h, w);
	int res = 0;
	for(int i = 0; i + p <= h; i++){
		for(int j = 0; j + p <= w; j++){
			if(s.find(hash[i][j]) != s.end()){
				res++;
			}
		}
	}
	return res;
}
int main(){
	for(int i = 0; i < 26; i++){
	       	cv[i + 65] = i;
		cv[i + 97] = i + 26;
	}
	for(int i = 0; i < 10; i++) cv[i + 48] = i + 52;
	cv[43] = 62;
	cv[47] = 63;

	while(scanf("%d %d %d\n", &w, &h, &p) && (w || h || p)){
		for(int i = 0; i < h; i++){
			string s;
			cin>>s;
			for(int j = 0; j < s.length(); j++){
				int t = cv[s[j]];
				for(int k = 0; k < 6 && j * 6 + k < w; k++){
					mat[i][j * 6 + k] = (t >> (5 - k)) & 1;
				}
			}
		}
		for(int i = 0; i < p; i++){
			string s;
			cin>>s;
			for(int j = 0; j < s.length(); j++){
				int t = cv[s[j]];
				for(int k = 0; k < 6 && j * 6 + k < p; k++){
					pattern[i][j * 6 + k] = (t >> (5 - k)) & 1;
				}
			}
		}
		printf("%d\n", solve());
	}
	return 0;
}

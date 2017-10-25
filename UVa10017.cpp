#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

struct P{
	vector<int> s;
	char peg;
	P(char peg) : peg(peg) {
		s.resize(0);
	}
	P(char peg, vector<int> s) : peg(peg), s(s) {}
};

int n, m;

void Hanoi(P& A, P& B, P& C, int d, int& count){
	if(d == 0){
		return;
	}
	Hanoi(A, C, B, d - 1, count);
	if(count >= m) return;

	C.s.push_back(A.s.back());
	A.s.pop_back();
	P p[] = {A, B, C};
	for(char ch = 'A'; ch <= 'C'; ch++){
		printf("%c=>", ch);
		for(int j = 0; j < 3; j++){
			if(ch == p[j].peg && p[j].s.size() > 0){
				printf("   ");
				for(int k = 0; k < p[j].s.size(); k++){
					printf("%d", p[j].s[k]);
					if(k < p[j].s.size() - 1) printf(" ");
				}
			}
		}
		printf("\n");
	}
	printf("\n");			
	Hanoi(B, A, C, d - 1, ++count);
}

void solve(){
	vector<int> s;	
	printf("A=>   ");
	for(int i = n; i >= 1; i--){
		printf("%d%c", i, i == 1 ? '\n' : ' ');
		s.push_back(i);
	}

	int count = 0;
	P A('A', s), B('B'), C('C');
	printf("B=>\nC=>\n\n");
	Hanoi(A, B, C, n, count);
}

int main(){
	int c = 1;
	while(cin>>n>>m && (n || m)){
		printf("Problem #%d\n\n", c++);
		solve();
	}
	return 0;
}

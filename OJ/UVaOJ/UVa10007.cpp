#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#define MAX_N 300

using namespace std;

struct BigInteger {
  static const int BASE = 100000000;
  static const int WIDTH = 8;
  vector<long long> s;

  BigInteger(long long num = 0) { *this = num; } // 构造函数
  BigInteger operator = (long long num) { // 赋值运算符
    s.clear();
    do {
      s.push_back(num % BASE);
      num /= BASE;
    } while(num > 0);
    return *this;
  }
  BigInteger operator = (const string& str) { // 赋值运算符
    s.clear();
    int x, len = (str.length() - 1) / WIDTH + 1;
    for(int i = 0; i < len; i++) {
      int end = str.length() - i*WIDTH;
      int start = max(0, end - WIDTH);
      sscanf(str.substr(start, end-start).c_str(), "%d", &x);
      s.push_back(x);
    }
    return *this;
  }
  BigInteger operator + (const BigInteger& b) const {
    BigInteger c;
    c.s.clear();
    for(int i = 0, g = 0; ; i++) {
      if(g == 0 && i >= s.size() && i >= b.s.size()) break;
      int x = g;
      if(i < s.size()) x += s[i];
      if(i < b.s.size()) x += b.s[i];
      c.s.push_back(x % BASE);
      g = x / BASE;
    }
    return c;
  }
  BigInteger operator + (const long long& b) const{
	  BigInteger c = b;
	  return c + (*this);
  }
  BigInteger operator * (const BigInteger& b) const{
	  BigInteger c;
	  c.s.resize(s.size(), 0);
	  for(int j = 0; j < b.s.size(); j++){
		  long long x = 0;
		  for(int i = 0;; i++){
			  if(x == 0 && i >= s.size()) break;
			  if(i < s.size()){
					x += s[i]*b.s[j];
			  }
			  if(i+j < c.s.size()) c.s[i+j] += x % BASE;
			  else c.s.push_back(x % BASE);
			  x = x / BASE + c.s[i+j] / BASE;
			  c.s[i+j] %= BASE;
		  }
	  }
	  return c;
  }
  BigInteger operator * (const long long& sum) const{
	  BigInteger c = sum;
	  return *this * c;
  }
  BigInteger operator / (const long long& b) const{
	  BigInteger c;
      c.s.clear();
	  long long x = 0;
	  vector<long long> temp;
	  for(int i = s.size()-1; i >= 0; i--){
		  x = x * BASE + s[i];
		  if(x / b == 0 && temp.size() > 0 || x / b > 0)temp.push_back(x / b);
		  x %= b;
	  }
	  for(int i = temp.size() -1 ; i >= 0; i--){
		  c.s.push_back(temp[i]);
	  }
	  return c;
  }
  long long operator % (const long long& b) const{
	  long long x = 0;
	  for(int  i = s.size()-1; i >= 0; i--){
		  x = x * BASE + s[i];
		  x %= b;
	  }
	  return x;
  }
};

ostream& operator << (ostream &out, const BigInteger& x) {
	//最後一個不一定是八個數字，所以要先輸出
  out << x.s.back();
  for(int i = x.s.size()-2; i >= 0; i--) {
    char buf[20];
    sprintf(buf, "%08d", x.s[i]);
    for(int j = 0; j < strlen(buf); j++) out << buf[j];
  }
  return out;
}

istream& operator >> (istream &in, BigInteger& x) {
  string s;
  if(!(in >> s)) return in;
  x = s;
  return in;
}

int n;
BigInteger fact[MAX_N+1];
BigInteger BST[MAX_N+1];

void fact_calc(){
	fact[0] = 1;
	for(int i = 1; i <= MAX_N; i++){
		fact[i] = fact[i-1] * i;
	}
}
void init(){
	BST[0] = 1;
	BST[1] = 1;
	fact_calc();
	for(int i = 1; i < MAX_N; i++){
		BST[i+1] = 0;
		for(int j = 0; j <= i; j++){
			BST[i+1] = BST[i+1] + BST[j] * BST[i-j];
		}
	}
}
BigInteger solve(){
	return BST[n] * fact[n];
}
int main(){
	init();
	while(cin>>n){
		if(!n) break;
		cout<<solve()<<endl;;
	}
	return 0;
}
		
		
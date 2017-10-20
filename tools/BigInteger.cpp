#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
/*
目前可用的用法：
(1)BigInteger * BigInteger
(2)BigInteger * int (or long long)
(3)BigInteger + BigInteger
(3)BigInteger + int (or long long)
(4)BigInteger / int (or long long)
(5)BigInteger % int (or long long)
(6)BigInteger - BigInteger......自己做...我好懶
P.S.我不太能保證乘法/除法運算一定正確....至少我測不出問題，但我也沒
測太多數據。會怕的就自己多測幾筆抓蟲吧，有找到就告訴我。
2017/9/30
除法運算幾乎可確定正常。
新增取模運算。
*/
using namespace std;

#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
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

int  main(){
    BigInteger A;
	int i;
    while(cin>>A>>i){
    	cout<<A/i<<endl;
    }
    return 0;
}

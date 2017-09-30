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
  bool is_zero(){
	  return s.size() == 0;
  }
  long long operator % (const int& b) const{
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
    sprintf(buf, "%08lld", x.s[i]);
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
int  D;
BigInteger m ,k;
int A[100];
int B[100];
vector<int> get_3_radix(BigInteger x){
	vector<int> s;
 	do{
		s.push_back(x % D);
		x = x / D;
	}while(!x.is_zero());
	return s;
}
long long gcd(long long a, long long b){
    if(b == 0){
		return a;
	}
    return gcd(b, a % b);
}
long long extgcd(long long a, long long b, long long& x, long long& y){
    long long d = a;
    if(b != 0){
	    d = extgcd(b, a % b, y, x);
	    y -= (a / b) * x;
    }else{
	    x = 1, y = 0;
    }
    return d;
}

long long mod_inverse(long long a, long long b){
   long long x, y;
   extgcd(a, b, x, y);
   return (b + x % b) % b;
}
long long linear_congruence(const vector<long long>& B, const vector<long long>& M){
    long long  x = 0, m = 1;
    for(int i = 0; i < B.size(); i++){
        long long a = m, b = B[i] - 1 * x, d = gcd(M[i], a);
        if(b % d != 0){
            return -1;
        }
        long long t = b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d);
		x = x + m * t;
		m *= M[i] / d;
    }
    return (x % m + m) % m;
}
void solve(){
    vector<int> s, t;
    s = get_3_radix(m);
    t = get_3_radix(k);
    if(s.size() != t.size()){
        cout<<"NO\n";
        return;
    }
    vector<long long> n, b;
    for(int i = 0; i < s.size(); i++){
        int p = 0;
        int x = s[i];
        do{
            if(t[i] == x) b.push_back(p);
            p++;
            if(i < s.size()-1) x = B[x];
            else x = A[x];
        }while(x != s[i]);
        n.push_back(p);
        if(b.size() != n.size()) {
            cout<<"NO\n";
            return;
        }
    }
	/*for(int i = 0; i < b.size(); i++){
		printf("b = %d  n = %d\n", b[i], n[i]);
	}
	cout<<endl;*/
    long long res = linear_congruence(b, n);
    if(res < 0) cout<<"NO\n";
    else cout<<res<<endl;
    /*for(int i = 0; i < B.size(); i++){
        printf("b = %d, n = %d\n", B[i], N[i]);
    }*/

}
int  main(){
    while(cin>>D){
		if(D < 0) break;
        for(int i = 1; i < D; i++){
            scanf("%d", A+i);
        }
        for(int i = 0; i < D; i++){
            scanf("%d", B+i);
        }
        cin>>m>>k;
        solve();
    }
    return 0;
}

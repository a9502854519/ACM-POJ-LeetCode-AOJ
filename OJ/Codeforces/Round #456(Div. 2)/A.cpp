#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
typedef long long ll;

ll A, B;
ll x, y, z;

ll solve(){
	ll a = 2 * x + y;
	ll b = y + 3 * z;
	ll res = 0;
	if(a - A > 0) res += a - A;
	if(b - B > 0) res += b - B;
	return res;
}
int main(){
	cin >> A >> B;
	cin >> x >> y >> z;
	cout << solve() << endl;
	return 0;
}
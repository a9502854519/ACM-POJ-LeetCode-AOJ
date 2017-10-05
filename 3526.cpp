#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#define EPS 1E-10
using namespace std;
typedef long long ll;
typedef vector<double> vec;
typedef vector<vec> mat;

double a, b;
int m ,n;
ll fact[21];
void init(){
    fact[0] = 1;
    for(int i = 1; i <= 20; i++){
        fact[i] = fact[i-1] * i;
    }
}
double get_comb(int i, int j){
    return (double)fact[i]/(fact[j] * fact[i-j]);
}
double my_pow(ll a, int b){
    double d = 1;
    while(b--) d *= a;
    return d;
}
void swap(vec& A, vec& B){
    vec t = A;
    A = B;
    B = t;
}
void Gauss_Jordan(mat& A){
    int n = A.size();
    for(int i = 0; i < n; i++){
        int pivot = i;
        for(int j = i; j < n; j++){
            if(abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        }
        swap(A[i], A[pivot]);
        for(int j = i+1; j <= n; j++) A[i][j] /= A[i][i];
 //       A[i][i] = 1;
        for(int j = 0; j < n; j++){
            if(i != j){
                for(int k = i+1; k <= n; k++) A[j][k] -= A[j][i] * A[i][k];
	//    	A[j][i] = 0;
            }
        }
//	printf("i = %d\n", i);
//	for(int a = 0; a < n; a++){
//	    for(int b = 0; b <= n; b++){
//	    	printf("%.2f ", A[a][b]);
//	    }
//	    cout<<endl;
//	}
//	cout<<endl;
    }
    printf("1 ");
    for(int i = n-1; i >= 0; i--){
        //printf("%lld ", A[i][n]);
        printf("%.0f ", abs(A[i][n]) < EPS ? 0 : A[i][n]);
    }
    printf("\n");
}
void solve(){
    int degree = m*n;
    mat A(degree, vec(degree+1, 0));
    A[0][0] = 1;
    for(int i = 1; i <= degree; i++){
        for(int j = 0; j <= i; j++){
            double c = get_comb(i, j);
            c *= my_pow(a, (i-j)/m) * my_pow(b, j/n);
            A[((i-j) % m) * n + j % n][i] += (i == degree ? -c : c);
        }
    }
    Gauss_Jordan(A);
}
int main(){
    init();
    while(scanf("%lf%d%lf%d", &a, &m, &b, &n) != EOF){
            if(a == 0.0 && b == 0.0 &&
               m == 0 && n == 0.0) break;
        solve();
    }
}

#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 20000 + 10
#define MAX_K 50000 + 10

using namespace std;

double V[MAX_N], E[MAX_K];
double sm[MAX_N];
int N, K;

double solve(){
    sort(V, V + N);
    double sum = 0;
    sm[0] = 0.0;
    for(int i = 0; i < N; i++){
        sum += V[i];
        sm[i + 1] = sm[i] + V[i];
    }
    E[0] = sum / N;
    
    for(int k = 1; k <= K; k++){
        int i = upper_bound(V, V + N, E[k - 1]) - V;
        E[k] = (E[k - 1] * i + sm[N] - sm[i]) / N;
    }
    return E[K];
}
int main(){
    int T;
    cin >> T;
    for(int kase = 1; kase <= T; kase++){
        cin >> N >> K;
        for(int i = 0; i < N; i++) cin >> V[i];
        printf("Case #%d: %.6f\n", kase, solve());
    }
    return 0;
}
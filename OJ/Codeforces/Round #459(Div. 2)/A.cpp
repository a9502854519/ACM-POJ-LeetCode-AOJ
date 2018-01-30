#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 1000 + 10

using namespace std;

int n;

int main(){
    int f1 = 1, f2 = 1;
    cin >> n;
    for(int i = 1; i <= n; i++){
        if(i == f2){
            cout << "O";
            int tmp = f2;
            f2 += f1;
            f1 = tmp;
        }else cout << "o";
    }
    return 0;
}
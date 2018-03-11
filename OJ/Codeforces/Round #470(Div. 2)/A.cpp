#include<iostream>
#include<cstdio>
#define MAX_R 500 + 10

using namespace std;

int R, C;
char m[MAX_R][MAX_R];

int dx[] = {0,  0, 1, -1};
int dy[] = {1, -1, 0,  0};
void solve(){
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            if(m[i][j] == 'W'){
                for(int k = 0; k < 4; k++){
                    int x = i + dx[k], y = j + dy[k];
                    if(x >= 0 && x < R && y >= 0 && y < C){
                        if(m[x][y] == 'S'){
                            cout << "No\n";
                            return;
                        }
                        else if(m[x][y] == '.') m[x][y] = 'D';
                    }
                }
            }
        }
    }
    cout << "Yes\n";
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cout << m[i][j];
        }
        cout << endl;
    }
}
int main(){
    cin >> R >> C;
    for(int i = 0; i < R; i++){
        scanf("%s", m[i]);
    }
    solve();
    return 0;
}
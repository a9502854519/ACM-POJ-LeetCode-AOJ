#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_map>
#define MAX_N 1000

using namespace std;

unordered_map<string, string> mp;
int n, m;

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        string name, ip;
        cin >> name >> ip;
        mp[ip] = name;
    }
    while(m--){
        string name, ip;
        cin >> name >> ip;
        cout << name << " " << ip << " #" << mp[ip.substr(0, ip.length() - 1)] << endl;
    }
}
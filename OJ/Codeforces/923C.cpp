#include<iostream>
#include<cstdio>
#include<cstring>
#define MAX_N 300000
#define MAX_DEPTH 29

using namespace std;

int N;
int A[MAX_N], P[MAX_N];
struct Node{
    Node *child[2];
    int cnt;
    Node(){
        child[0] = child[1] = NULL;
        cnt = 0;
    }
};
Node head;

void insert(int v){
    Node* node = &head;
    int level = MAX_DEPTH;
    
    while(level >= 0){
        int tmp = (v >> level) & 1;
        if(node->child[tmp] == NULL) node->child[tmp] = new Node;
        
        level--;
        node = node->child[tmp];
    }
    node->cnt++;
}
int query(int v){
    Node* node = &head;
    int level = MAX_DEPTH, res = 0;
    
    while(level >= 0){
        int tmp = (v >> level) & 1;
        if(node->child[tmp] == NULL) tmp ^= 1;
        
        res = res | (tmp << level);
        node = node->child[tmp];
        level--;
    }
    node->cnt--;
    return res;
}
bool del(int v, int level, Node *node){
    if(level < 0) return node->cnt == 0;
    
    int tmp = (v >> level) & 1;
    if(del(v, level - 1, node->child[tmp])){
        delete node->child[tmp];
        node->child[tmp] = NULL;
    }
    return node->child[0] == NULL && node->child[1] == NULL;
}
void solve(){
    for(int i = 0; i < N; i++){
        insert(P[i]);
    }
    for(int i = 0; i < N; i++){
        int tmp = query(A[i]);
        printf("%d ", tmp ^ A[i]);
        del(tmp, MAX_DEPTH, &head);
    }
    cout << endl;
}
int main(){
    cin >> N;
    for(int i = 0; i < N; i++) scanf("%d", A + i);
    for(int i = 0; i < N; i++) scanf("%d", P + i);
    solve();
    return 0;
}
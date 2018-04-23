int rank[MAX_N + 1];
int tmp[MAX_N + 1];
int n, k;

bool compare_sa(int i, int j){
    if(rank[i] != rank[j]) return rank[i] < rank[j];
    else{
        int ri = i + k <= n ? rank[i + k] : -1;
        int rj = j + k <= n ? rank[j + k] : -1;
        return ri < rj;
    }
}
void construct_sa(string S, int *sa){
    n = S.length();
    
    for(int i = 0; i <= n; i++){
        sa[i] = i;
        rank[i] = i < n : S[i] : -1;
    }
    
    for(k = 1; k <= n; k *= 2){
        sort(sa, sa + n + 1, compare_sa);
        tmp[sa[0]] = 0;
        for(int i = 1; i <= n; i++){
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for(int i = 0; i <= n; i++){
            rank[i] = tmp[i];
        }
    }
}
void construct_lcp(string S, int *sa, int *lcp){
    n = S.length();
    for(int i = 0; i <= n; i++) rank[sa[i]] = i;
    
    int h = 0;
    lcp[0] = 0;
    for(int i = 0; i < n; i++){
        int j = sa[rank[i] - 1];
        if(h > 0) h--;
        for(; j + h < n && i + h < n; h++){
            if(S[j + h] != S[i + h]) break;
        }
        lcp[rank[i] - 1] = h;
    }
}
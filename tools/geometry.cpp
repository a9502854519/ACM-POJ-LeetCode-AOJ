struct P{
    ll x, y;
    P() {}
    P(ll x, ll y) : x(x), y(y) {}
    
    P operator + (const P& p) const{
        return P(x + p.x, y + p.y);
    }
    P operator - (const P& p) const{
        return P(x - p.x, y - p.y);
    }
    ll dot(const P& p) const{
        return x * p.x + y * p.y;
    }
    ll det(const P& p) const{
        return x * p.y - y * p.x;
    }
};

double EPS = 1e-10;
struct P{
    double x, y;
    P() {}
    P(double x, double  y) : x(x), y(y) {}
    
    P operator + (const P& p) const{
        return P(add(x + p.x), add(y + p.y));
    }
    P operator - (const P& p) const{
        return P(add(x, - p.x), add(y, - p.y));
    }
    ll dot(const P& p) const{
        return add(x * p.x, y * p.y);
    }
    ll det(const P& p) const{
        return add(x * p.y, -y * p.x);
    }
};
vector<P> convex_hull(){
    int k = 0;
    vector<P> qs(n * 2);
    for(int i = 0; i < n; i++){
        while(k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    
    for(int i = n - 2, t = k; i >= 0; i--){
        while(k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}
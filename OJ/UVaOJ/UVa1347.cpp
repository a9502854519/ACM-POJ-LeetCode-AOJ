#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX_N 100000
#define INF 1E9

using namespace std;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
};

int n;
vector<Point> v;
double dp[MAX_N];
double dist[MAX_N];

double distance(Point a, Point b)
{
    double x, y;
    x = (a.x - b.x) * (a.x - b.x);
    y = (a.y - b.y) * (a.y - b.y);
    return sqrt(x + y);
}
void solve() 
{
    n = v.size();
    for (int i = n - 1; i >= 0; i--) {
        v[i].x -= v[0].x;
        v[i].y -= v[0].y;
    }

    dist[0] = 0.0;
    for (int i = 1; i < n; i++) {
        dist[i] = distance(v[i], v[i - 1]) + dist[i - 1];
    }

    dp[1] = dist[1];
    for (int i = 2; i < n; i++) {
        dp[i] = INF;
        for (int j = 0; j < i - 1; j++) {
            // i is connected to j
            dp[i] = min(dp[i], dp[j + 1] + dist[i - 1] - dist[j + 1] + distance(v[i], v[j]));
        }
    }
    double res = dp[n - 1] + distance(v[n - 1], v[n - 2]);
    printf("%.2lf\n", res);
}

int main() 
{
    while(scanf("%d\n", &n) != EOF) {
        double x, y;
        v.clear();

        while (n--) {
            scanf("%lf %lf\n", &x, &y);
            v.push_back(Point(x, y));
        }

        solve();
    }
    return 0;
}
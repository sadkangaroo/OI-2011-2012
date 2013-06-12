#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

#define LC(x) (x * 2)
#define RC(x) (x * 2 + 1)
#define NEG(x) (x < -eps)
#define POS(x) (x > eps)

const int MaxN = 1005;
const double eps = 1e-9;

int N, tot;
double xa, ya, xb, yb, ans;
double ys[MaxN * 2];

double sum[MaxN * 2 * 4], sum2[MaxN * 2 * 4];
int cnt[MaxN * 2 * 4];

struct Line {
    double x, ya, yb;
    int t;
    bool operator < (const Line &t)const {return x < t.x;}
    Line(double _x, double _ya, double _yb, int _t) {
        x = _x; ya = _ya; yb = _yb; t = _t;
    }
}; vector<Line> e;

void Modify(int p, int l, int r, double a, double b, int t) {
    if (!POS(a - ys[l]) && !NEG(b - ys[r])) {
        cnt[p] += t;
        if (cnt[p] > 0) sum[p] = ys[r] - ys[l];
            else {
                sum[p] = (l + 1 == r) ? 0 : (sum[LC(p)] + sum[RC(p)]);
                sum2[p] = (l + 1 == r) ? 0 : (sum2[LC(p)] + sum2[RC(p)]);
            }
        if (cnt[p] > 1) sum2[p] = ys[r] - ys[l];
            else if (cnt[p] == 1) 
                sum2[p] = (l + 1 == r) ? 0 : (sum[LC(p)] + sum[RC(p)]);
        return;
    }
    int mid = (l + r) / 2;
    if (NEG(a - ys[mid])) Modify(LC(p), l, mid, a, b, t);
    if (POS(b - ys[mid])) Modify(RC(p), mid, r, a, b, t);
    if (cnt[p] == 0) {
        sum[p] = sum[LC(p)] + sum[RC(p)];
        sum2[p] = sum2[LC(p)] + sum2[RC(p)];
    }
    if (cnt[p] == 1) sum2[p] = sum[LC(p)] + sum[RC(p)];
}

void UniqueIt() {
    int tmp = tot;
    tot = 0; ys[tmp + 1] = -1;
    for (int i = 1; i <= tmp; ++i) {
        if (ys[i] == ys[i + 1]) continue;
        tot++;
        ys[tot] = ys[i];
    }
}

void Init() {
    scanf("%d", &N);
    tot = 0; e.clear();
    for (int i = 1; i <= N; ++i) {
        scanf("%lf%lf%lf%lf", &xa, &ya, &xb, &yb);
        ys[++tot] = ya; ys[++tot] = yb;
        e.push_back(Line(xa, ya, yb, 1)); e.push_back(Line(xb, ya, yb, -1));
    }
    sort(ys + 1, ys + tot + 1);
    UniqueIt();
    sort(e.begin(), e.end());
    for (int i = 0; i < MaxN * 2 * 4; ++i)
        sum[i] = sum2[i] = 0;
    memset(cnt, 0, sizeof(cnt));
}

void Solve() {
    ans = 0;
    for (int i = 0; i < e.size() - 1; ++i) {
        Modify(1, 1, tot, e[i].ya, e[i].yb, e[i].t);
        ans += (sum2[1] * (e[i + 1].x - e[i]. x));
    }
    printf("%.2lf\n", ans);
}

int main() {

    int T;
    scanf("%d", &T);
    while (T--) {
        Init();
        Solve();
    }

    return (0-0);

}

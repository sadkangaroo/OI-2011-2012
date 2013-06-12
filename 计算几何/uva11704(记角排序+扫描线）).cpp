#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int Max_N = 30005;
const double pi = acos(-1);

bool f;
int C, P, tot;
double xi, yi, d;
int a[Max_N], b[Max_N], pos;

struct node {
    double x, y, deg;
    int lab;
    node(){}
    node(double _x, double _y, int _lab) {
        x = _x; y = _y; lab = _lab;
        deg = atan2(y, x);
    }
    bool operator < (const node &t)const {return deg < t.deg;}
}pt[Max_N];

void Init() {
    tot = C + P;
    for (int i = 1; i <= C; ++i) {
        scanf("%lf%lf", &xi, &yi);
        pt[i] = node(xi, yi, 0);
    }
    for (int i = C + 1; i <= tot; ++i) {
        scanf("%lf%lf", &xi, &yi);
        pt[i] = node(xi, yi, 1);        
    }
    sort(pt + 1, pt + 1 + tot);
    a[0] = b[0] = 0;
    for (int i = 1; i <= tot; ++i)
        if (pt[i].lab == 0) a[i] = a[i - 1] + 1, b[i] = b[i - 1];
            else a[i] = a[i - 1], b[i] = b[i - 1] + 1;
}

int search(double d) {
    int l = 1, r = tot +1, mid;
    while (l + 1 < r) {
        mid = (l + r) >> 1;
        if(pt[mid].deg < d) l = mid;
            else r = mid;
    }
    if (pt[l].deg > d) l = 0;
    return l;
}

void Solve() {
    for (int i = 1; i <= tot; ++i) {
        d = pt[i].deg + pi;
        if (d > pi) d -= (2 * pi);
        pos = search(d);        
        if (abs(a[pos] - a[i]) * 2 == C && abs(b[pos] - b[i]) * 2 == P)
             f = true;
        if (pos > i) {
            if (pt[i].lab == 0)  
                if ((a[pos] - a[i] + 1) * 2 == C && (b[pos] - b[i]) * 2 == P)
                    f = true;
            if (pt[i].lab == 1) 
                if ((a[pos] - a[i]) * 2 == C && (b[pos] - b[i] + 1) * 2 == P)
                    f = true;
        }
        else {
            if (pt[i].lab == 0)
                if ((a[i] - a[pos] - 1) * 2 == C && (b[i] - b[pos]) * 2 == P)
                    f = true;
            if (pt[i].lab == 1) 
                if ((a[i] - a[pos]) * 2 == C && (b[i] - b[pos] - 1) * 2 == P)
                    f = true;
        }
    }
}

int main() {

    while (scanf("%d%d", &C, &P) && C != -1) {
        f = false;
        Init();
        Solve();    
        if (f) puts("YES");
            else puts("NO");    
    }

    return (0-0);

}

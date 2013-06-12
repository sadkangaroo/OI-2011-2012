#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int Max_N = 10005;
const double eps = 1e-7;

int N;
double sx, sy, soex[2], soey[2];
double x[Max_N], y[Max_N], ansx[Max_N], ansy[Max_N];

inline bool eq(double x, double y) {return fabs(x - y) < eps;}

void Init() {
    sx = sy = 0;
    soex[0] = soex[1] = soey[0] = soey[1] = 0;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%lf%lf", x + i, y + i);
        sx += x[i]; sy += y[i];    
        soex[i % 2] += x[i]; soey[i % 2] += y[i];
    }
}

void MakeIt() {
    for (int i = 2; i <= N; ++i) {
        ansx[i] = 2.0 * x[i - 1] - ansx[i - 1];
        ansy[i] = 2.0 * y[i - 1] - ansy[i - 1];
    }
    printf("YES\n");
    for (int i = 1; i <= N; ++i)
        printf("%.3lf %.3lf\n", ansx[i], ansy[i]);
}

void Solve() {
    if (N % 2 == 0) {
        if (eq(soex[0], soex[1]) && eq(soey[0], soey[1])) {
           ansx[1] = ansy[1] = 0;
           MakeIt(); 
        }
        else printf("NO\n");
    }
    else {
        ansx[1] = sx - soex[0] * 2.0;
        ansy[1] = sy - soey[0] * 2.0;
        MakeIt();
    }
}

int main() {

    Init();
    Solve();

    return (0-0);

}

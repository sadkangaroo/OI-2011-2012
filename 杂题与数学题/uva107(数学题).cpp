#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const double eps = 1e-7;

int a, b, lim;
double _n, _np1, n, np1, ans1, ans2;

int main() {

    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);

    while (scanf("%d%d", &a, &b) && a) {
        if (a == 1 && b == 1) {printf("0 1\n");continue;}
        lim = (int)(log(a) / log(2)) + 1;
        for (int k = 1; k <= lim; ++k) {
            _np1 = pow(a, 1.0 / k); _n = pow(b, 1.0 / k);
            np1 = floor(_np1 + 0.5); n = floor(_n + 0.5);
            if (fabs(np1 - _np1) < eps && fabs(n - _n) < eps) 
                if (fabs(np1 - n - 1) < eps) {
                    if (fabs(n - 1) < eps) ans1 = k;
                        else ans1 = ((double)(b - 1)) / (n - 1);
                    ans2 = a * np1 - b * n;
                    printf("%d %d\n", (int)(ans1 + 0.5), (int)(ans2 + 0.5));
                    break;
                }
        }
    }

    return (0-0);

}

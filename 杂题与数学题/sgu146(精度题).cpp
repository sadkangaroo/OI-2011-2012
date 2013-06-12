#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long LLd;

double len;
int N;
LLd L, ti, vi, s;

int main() {

    scanf("%lf%d", &len, &N);
    L = (LLd)(len * 10000.0 + 0.5);
    s = 0;
    while (N--) {
        scanf("%I64d%I64d", &ti, &vi);
        s = (s + (ti * vi * 10000LL) % L) % L;
    }
    if (s > (L / 2LL)) s = L - s;
    printf("%.4lf\n", (double)s / 10000.0);
    
    return (0-0);

}

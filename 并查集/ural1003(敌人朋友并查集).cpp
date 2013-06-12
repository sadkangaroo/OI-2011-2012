#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MaxNum = 5005 * 2, MaxQ = 5005;

int n, Q;
int a[MaxQ], b[MaxQ], num[MaxNum], p, fa[MaxNum], enm[MaxNum];
char oe[MaxQ][5];

int UniqueIt(int len) {
    int p = 0; num[len] = -1;
    for (int i = 0; i < len; ++i) {
        if (num[i] == num[i + 1]) continue;
        num[p++] = num[i];
    } 
    return p;
}

void Init() {
    scanf("%d", &Q);
    p = 0;
    for (int i = 1; i <= Q; ++i) {
        scanf("%d%d %s", a + i, b + i, &oe[i]);
        a[i]--; num[p++] = a[i]; num[p++] = b[i];
    }
    sort(num, num + p);
    p = UniqueIt(p);
}

int Grand(int x) {
    if (x == -1) return -1;
    if (fa[x] == x) return x;
    fa[x] = Grand(fa[x]);
    return fa[x];
}

void Solve() {
    int x, y, fx, fy, t;
    for (int i = 0; i < p; ++i) fa[i] = i;
    memset(enm, -1, sizeof(enm));
    int i;
    for (i = 1; i <= Q; ++i) {
        x = lower_bound(num, num + p, a[i]) - num;
        y = lower_bound(num, num + p, b[i]) - num;
        fx = Grand(x); fy = Grand(y);
        if (oe[i][0] == 'e') {
            if (fx == fy) continue;
            if (Grand(enm[fx]) == fy) break;
            fa[fx] = fy;
            if (enm[fx] != -1) enm[fy] = enm[fx];
        }
        else {
            if (fx == fy) break;
            t = Grand(enm[fx]);
            if (t == fy) continue;
            if (t != -1) fa[t] = fy; 
            enm[fx] = fy; enm[fy] = fx;
        }
    }
    printf("%d\n", i - 1);
}

int main() {
    
    while (scanf("%d", &n) && n != -1) {
        Init();
        Solve();
    }
    
    return 0;

}

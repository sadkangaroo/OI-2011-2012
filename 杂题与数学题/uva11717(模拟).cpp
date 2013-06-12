#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int oo = 0x7fffffff;

int T, idle, ignore, n, fall, wake, now, x;
long long t[2];

int main() {
    
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        scanf("%d%d%d", &n, &fall, &wake);
        idle = ignore = 0;
        t[now = 0] = 0;
        for (int i = 1; i <= n; ++i) {
            now ^= 1;
            scanf("%d", &x);
            t[now] = x;
            if (t[now] < t[now ^ 1] ) {ignore++; t[now] = t[now ^ 1];}
            if (t[now] - t[now ^ 1] >= fall) {idle++; t[now] += wake;}
        }
        printf("Case %d: %d %d\n", tc, idle, ignore);
    }
    
    return 0;

}

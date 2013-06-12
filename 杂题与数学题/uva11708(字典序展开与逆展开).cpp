#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long LLd;

const int MaxN = 20;

char s[MaxN], a[MaxN];
int len, rank[MaxN];
bool vis[MaxN];
LLd C[MaxN][MaxN], fact[MaxN], f[MaxN];

void Init() {
    fact[0] = 1;
    for (int i = 1; i < MaxN; ++i)
        fact[i] = fact[i - 1] * i;
    for (int i = 0; i < MaxN; ++i)
        for (int j = 0; j <= i; ++j)
            if (j == 0 || j == i) C[i][j] = 1;
                else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    memset(f, 0, sizeof(f));
    for (int i = 0; i < MaxN; ++i)
        for (int j = 0; j <= i; ++j)
            f[i] += (C[i][j] * fact[j]);
}

void GetRank() {
    for (int i = 0; i < len; ++i) {
        rank[i] = 1;
        for (int j = i + 1; j < len; ++j)
            if (s[j] < s[i]) rank[i]++;
    }
}

char select(int r) {
    int i;
    for (i = 0; i < len; ++i) {
        if (!vis[i]) r--;
        if (!r) break;
    }
    vis[i] = true;
    return a[i];
}

void Solve() {
    LLd x; int r;
    while (gets(s)) {
        len = strlen(s);
        memcpy(a, s, sizeof(s));
        sort(a, a + len);
        GetRank();
        LLd ans = 0;
        for (int i = 0; i < len; ++i)
            ans += ((rank[i] - 1) * f[len - i - 1] + 1);
        printf("%lld\n", ans);
        while (scanf("%lld", &x) == 1) {
            x++;
            memset(vis, false, sizeof(vis));
            for (int k = len - 1; k >= 0; --k) {
                if (x == 1) break;
                r = (x - 1) / f[k];
                if ((x - 1) % f[k]) r++;
                putchar(select(r));
                x = x - 1 - (r - 1) * f[k];
            }
            puts("");
        }
    }
}

int main() {

    Init();
    Solve();

    return (0-0);

}

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

const int MaxLen = 10 * 2 + 5, MaxN = 1005;

map<string, int> Name;

int N, R, a, b, ans;
int t, stk[MaxN];
char s[MaxLen];
bool g[MaxN][MaxN], gr[MaxN][MaxN], vis[MaxN];

void Init() {
    Name.clear();
    for (int i = 1; i <= N; ++i) {
        gets(s);
        Name[(string)s] = i;
    }
    memset(g, false, sizeof(g));
    memset(gr, false, sizeof(gr));
    for (int i = 1; i <= R; ++i) {
        gets(s); a = Name[(string)s];
        gets(s); b = Name[(string)s];
        g[a][b] = gr[b][a] = true;
    }
}

void Dfs(int p) {
    vis[p] = true;
    for (int i = 1; i <= N; ++i)
        if (g[p][i] && !vis[i]) Dfs(i);
    stk[++t] = p;
}

void Rdfs(int p) {
    vis[p] = true;
    for (int i = 1; i <= N; ++i)
        if (gr[p][i] && !vis[i]) Rdfs(i);
}

void Solve() {
    ans = t = 0;
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= N; ++i)
        if (!vis[i]) Dfs(i);
    memset(vis, false, sizeof(vis));
    for (; t; --t) if (!vis[stk[t]]) ans++, Rdfs(stk[t]);
    printf("%d\n", ans);
}

int main() {
    
    while (scanf("%d%d ", &N, &R) && N) {
        Init();
        Solve();
    }
    
    return 0;

}

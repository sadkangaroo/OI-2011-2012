#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MaxN = 300 + 5;
const int oo = 0x7fffffff;

int N, M, Q;
int S, T, d[MaxN], gg[MaxN][MaxN], g[MaxN][MaxN], v[MaxN], flow, aug;
int mf[MaxN][MaxN], parent[MaxN];
bool found, vis[MaxN];

void Init() {
    int a, b, c;
    memset(gg, 0, sizeof(gg));
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        gg[a][b] += c; gg[b][a] += c;
    }
    memset(mf, 0, sizeof(mf));
}

void augment(int p) {
    int tmp = aug, mind = N - 1;
    if (p == T) {
        found = true;
        flow += aug;
        return; 
    }
    int i;
    for (i = 1; i <= N; ++i) {
        if (g[p][i] == 0) continue;
        if (d[p] == d[i] + 1) {
            if (g[p][i] < aug) aug = g[p][i];
            augment(i);
            if (d[S] >= N) return;
            if (found) break;
            aug = tmp;
        }
        if (d[i] < mind) mind = d[i];
    }
    if (found) {
       g[p][i] -= aug;
       g[i][p] += aug;    
    }
    else {
        if (--v[d[p]] == 0) d[S] = N;
        d[p] = mind + 1;
        v[d[p]]++;
    }   
}

void SAP() { 
    memcpy(g, gg, sizeof(gg));
    memset(d, 0, sizeof(d));
    memset(v, 0, sizeof(v));
    v[0] = N;
    flow = 0;  
    while (d[S] < N) {
        aug = oo;
        found = false;
        augment(S);
    }  
}

void Dfs(int p) {
    vis[p] = true;
    for (int i = 1; i <= N; ++i)
         if (g[p][i] && !vis[i]) Dfs(i);
}

void Solve() {
    for (int i = 1; i <= N; ++i) parent[i] = 1;
    for (int i = 2; i <= N; ++i) {
        S = parent[i]; T = i;
        SAP();
        mf[S][T] = mf[T][S] = flow;
        memset(vis, false, sizeof(vis));
        Dfs(S);
        for (int j = i + 1; j <= N; ++j) 
            if (!vis[j] && parent[j] == S) parent[j] = T;
        for (int j = 1; j < i; ++j) 
            if (j != S) mf[T][j] = mf[j][T] = min(mf[j][S], mf[S][T]);
    }
}

void Ans() {
    scanf("%d", &Q);
    int s, t;
    for (int i = 1; i <= Q; ++i) {
        scanf("%d%d", &s, &t);
        printf("%d\n", mf[s][t]);
    }
}

int main() {

    freopen("t3.in", "r", stdin);
    freopen("t3.out", "w", stdout);
    
    Init();
    Solve();
    Ans();
    
    return 0;

}

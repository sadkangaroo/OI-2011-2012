#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxNode = 100000 + 5, MaxE = MaxNode;
const int MaxP = 20;

int T, N;
int din[MaxNode], depth[MaxNode], f[MaxNode][MaxP];

struct etype {
    int t; etype *nxt;
    etype() {}
    etype(int _t, etype* _nxt): t(_t), nxt(_nxt) {}
    void* operator new(size_t, void* p) {return p;}
}*e[MaxNode], buf[MaxE], *cbuf;

void dfs(int now) {
     for (int i = 1; i < MaxP; ++i)
         f[now][i] = f[f[now][i - 1]][i - 1];
     for (etype* u = e[now]; u; u = u->nxt)
         depth[u->t] = depth[now] + 1, f[u->t][0] = now, dfs(u->t);
}

void GoUp(int &a, int d) {
     for (int i = 0; i < MaxP; ++i)
         if (d & (1 << i)) a = f[a][i];
}

int LCA(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    GoUp(a, depth[a] - depth[b]);
    if (a == b) return a;
    for (int i = MaxP - 1; i >= 0; --i) 
        if (f[a][i] != f[b][i]) 
           a = f[a][i], b = f[b][i];
    return f[a][0];
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    scanf("%d", &T);
    while (T--) {
         scanf("%d", &N); int a, b;
         cbuf = buf; memset(e, 0, sizeof(e));
         memset(din, 0, sizeof(din));
         for (int i = 1; i < N; ++i) {
             scanf("%d%d", &a, &b); din[b]++;
             e[a] = new(cbuf++)etype(b, e[a]);
         } 
         memset(f, 0, sizeof(f));
         for (int i = 1; i <= N; ++i) 
             if (din[i] == 0) {depth[i] = 0; dfs(i); break;}
         scanf("%d%d", &a, &b);
         printf("%d\n", LCA(a, b));
    }

    return 0;

}

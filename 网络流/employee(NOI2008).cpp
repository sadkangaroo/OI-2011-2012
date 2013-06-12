#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>

using namespace std;

const int MaxN = 1000 + 5, MaxM = 10000 + 5;
const int MaxNode = MaxN * 2 + 5, MaxE = MaxN * 8 + MaxM * 2;
const int oo = 0x7fffffff;

#define id1(x) ((x) * 2)
#define id2(x) ((x) * 2 + 1)

int N, M, S, T, Num, ans;
int d[MaxNode], vis[MaxNode], pre[MaxNode];
queue<int> Q;

struct etype {
    int t, c, v;
    etype *nxt, *p;
    etype() {}
    etype(int _t, int _c, int _v, etype* _nxt): 
        t(_t), c(_c), v(_v), nxt(_nxt) {}
    void* operator new(unsigned, void* p) {return p;}
}*e[MaxNode], buf[MaxE], *cbuf = buf, *r[MaxNode];

void MakeEdge(int a, int b, int cab, int cba, int vab, int vba) {
     e[a] = new(cbuf++)etype(b, cab, vab, e[a]);
     e[b] = new(cbuf++)etype(a, cba, vba, e[b]);
     e[a]->p = e[b]; e[b]->p = e[a];
}

bool aug() {
    memset(vis, 0, sizeof(vis)); vis[S] = 1;
    for (int i = 0; i < Num; ++i) d[i] = ((i == S)? 0: oo);
    Q.push(S); int o, Max = oo, Cost = 0;
    while (!Q.empty()) {
          o = Q.front(); Q.pop(); vis[o] = 0;
          for (etype* u = e[o]; u; u = u->nxt)
              if (u->c && d[o] + u->v < d[u->t]) {
                 d[u->t] =  d[o] + u->v; r[u->t] = u; pre[u->t] = o;
                 if (!vis[u->t]) {Q.push(u->t); vis[u->t] = 1;}
              }
    }
    if (d[T] == oo) return false;
    for (int i = T; i != S; i = pre[i]) Max = min(Max, r[i]->c);
    for (int i = T; i != S; i = pre[i]) {
        Cost += r[i]->v; r[i]->c -= Max; r[i]->p->c += Max;
    } ans += Max * Cost; return true;
}

int main() {

    freopen("employee.in", "r", stdin);
    freopen("employee.out", "w", stdout);

    scanf("%d%d", &N, &M); int x, si, ti, ci;
    Num = 2 * N + 2; S = Num - 2; T = Num - 1;
    memset(e, 0, sizeof(e));
    for (int i = 0; i < N; ++i) {
        scanf("%d", &x);
        MakeEdge(S, id1(i), x, 0, 0, 0);
        MakeEdge(id2(i), T, x, 0, 0, 0);
        MakeEdge(id2(i), id1(i), oo, 0, 0, 0);
        if (i != N - 1) MakeEdge(id1(i), id2(i + 1), oo, 0, 0, 0);
    } 
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &si, &ti, &ci); si--; ti--;
        MakeEdge(id1(ti), id2(si), oo, 0, ci, -ci);
    }
    ans = 0; while(aug()) {}
    cout << ans << endl;
        
    return 0;

}

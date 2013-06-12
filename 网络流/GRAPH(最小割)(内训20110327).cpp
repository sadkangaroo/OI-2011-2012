#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 500 + 5, MaxM = 2000 + 5;
const int MaxE = MaxN * 2 + MaxM * 2 + 5;
const int oo = 0x7fffffff;

typedef long long LL;

struct etype {
    int t, c;
    etype *p, *nxt;
    etype(){}
    etype(int _t, int _c, etype* _nxt):t(_t), c(_c), nxt(_nxt){}
    void* operator new(unsigned, void* p){return p;}
}*e[MaxN], *bak[MaxN], buf[MaxE], bufbak[MaxE], *cbuf = buf, *cbak, np;

LL MaxEValue, MaxPValue;
int N, M, cnt;
bool vis[MaxN];
int val[MaxN], d[MaxN], v[MaxN];

void Init() {
     scanf("%d%d", &N, &M);
     for (int i = 1; i <= N; ++i) scanf("%d", val + i);
     int x, y;
     memset(e, 0, sizeof(e));
     for (int i = 1; i <= M; ++i) {
         scanf("%d%d", &x, &y);
         e[x] = new(cbuf++)etype(y, 1, e[x]);
         e[y] = new(cbuf++)etype(x, 1, e[y]);
         e[x]->p = e[y]; e[y]->p = e[x];
     }
     cbak = cbuf; memcpy(bak, e, sizeof(e));
     memcpy(bufbak, buf, (cbuf - buf) * sizeof(etype));
}

int aug(int now, int Max) {
    if (now == N + 1) return Max;
    int Rest = Max, mind = N + 2;
    for (etype* u = e[now]; u; u = u->nxt) if (u->c) {
        if (Rest && d[u->t] + 1 == d[now]) {
           int dt = aug(u->t, min(u->c, Rest));
           Rest -= dt; u->c -= dt; u->p->c += dt;
           if (d[0] >= N + 2) return Max - Rest;
        }
        if (u->c) mind = min(mind, d[u->t] + 1);
    }
    if (Rest == Max) if (!--v[d[now]]) d[0] = N + 2; else ++v[d[now] = mind];
    return Max - Rest;
}

void dfs(int now) {
     vis[now] = true; cnt++;
     for (etype* u = e[now]; u; u = u->nxt) 
         if (!vis[u->t] && u->c) dfs(u->t);
}

void Solve(int k) {
     cbuf = cbak; memcpy(e, bak, sizeof(e)); 
     memcpy(buf, bufbak, (cbuf - buf) * sizeof(etype));
     for (int i = 1; i <= N; ++i) if (val[i] >= 0) {
         if (val[i] & (1 << k)) 
            e[0] = new(cbuf++)etype(i, oo, e[0]), e[0]->p = &np;
         else e[i] = new(cbuf++)etype(N + 1, oo, e[i]), e[i]->p = &np;
     }
     memset(v, 0, sizeof(v)); memset(d, 0, sizeof(d));
     v[0] = N + 2;
     while (d[0] < N + 2) MaxEValue += ((LL)aug(0, oo) << k);
     memset(vis, false, sizeof(vis));
     cnt = -1; dfs(0);
     MaxPValue += ((LL)cnt << k);
}

int main() {

    freopen("GRAPH.in", "r", stdin);
    freopen("GRAPH.out", "w", stdout);

    Init();
    MaxEValue = MaxPValue = 0;
    for (int i = 0; i < 30; ++i) Solve(i);
    cout << MaxEValue << endl << MaxPValue << endl;

    return 0;

}

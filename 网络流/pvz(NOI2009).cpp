#include<iostream>
#include<algorithm>

using namespace std;

const int MaxN = 20 + 5, MaxM = 30 + 5, MaxNode = MaxN * MaxM;
const int MaxE = MaxNode * MaxNode * 2 + MaxNode * 2;
const int oo = 0x7fffffff;

#define id(x, y) ((x) * M + (y))

int N, M, W, S, T, Num, ans;
int score[MaxNode], din[MaxNode], vec[MaxNode], v[MaxNode], d[MaxNode];
bool adj[MaxNode][MaxNode], legal[MaxNode];

struct etype {
    int t, c;
    etype *nxt, *p;
    etype() {}
    etype(int _t, int _c, etype* _nxt): t(_t), c(_c), nxt(_nxt) {}
    void* operator new(unsigned, void* p) {return p;} 
}*e[MaxNode], buf[MaxE], *cbuf = buf, np;

void Init() {
     scanf("%d%d", &N, &M); int x, y;
     memset(din, 0, sizeof(din)); memset(adj, false, sizeof(adj));
     for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
         int lab = id(i, j); scanf("%d", score + lab);
         scanf("%d", &W); 
         for (int k = 0; k < W; ++k) {
             scanf("%d%d", &x, &y);
             if (!adj[lab][id(x, y)])
                adj[lab][id(x, y)] = true, din[id(x, y)]++;
         }
         if (j && !adj[lab][id(i, j - 1)]) {
            adj[lab][id(i, j - 1)] = true, din[id(i, j - 1)]++;
         }
     } 
     memset(legal, false, sizeof(legal)); int top = 0, cnt; 
     for (int i = 0; i < N * M; ++i) 
         if (din[i] == 0) legal[i] = true, vec[top++] = i;
     while (top) {
           cnt = vec[top - 1]; top--;
           for (int i = 0; i < N * M; ++i)
               if (adj[cnt][i]) 
                  if (!--din[i]) vec[top++] = i, legal[i] = true;
     }
}

void MakeGraph() {
     Num = 0;
     for (int i = 0; i < N * M; ++i) if (legal[i]) Num++;
     S = Num; T = Num + 1; Num += 2; ans = 0;
     memset(e, 0, sizeof(e));
     for (int i = 0; i < N * M; ++i) for (int j = 0; j < N * M; ++j)
         if (legal[i] && legal[j] && adj[j][i]) {
            e[i] = new(cbuf++)etype(j, oo, e[i]);
            e[j] = new(cbuf++)etype(i, 0, e[j]);
            e[i]->p = e[j]; e[j]->p = e[i];
         }
     for (int i = 0; i < N * M; ++i) if (legal[i])
         if (score[i] > 0) {
            ans += score[i];
            e[S] = new(cbuf++)etype(i, score[i], e[S]); e[S]->p = &np;
         }
         else {e[i] = new(cbuf++)etype(T, -score[i], e[i]); e[i]->p = &np;}
}

int aug(int now, int Max) {
    if (now == T) return Max;
    int Rest = Max, dmin = Num, dt;
    for (etype* u = e[now]; u; u = u->nxt) if (u->c) {
        if (Rest && d[u->t] + 1 == d[now]) {     
           dt = aug(u->t, min(u->c, Rest));
           Rest -= dt; u->c -= dt; u->p->c += dt;
           if (d[S] >= Num) return Max - Rest;
        }
        if (u->c) dmin = min(dmin, d[u->t] + 1);
    }
    if (Max == Rest) if (!--v[d[now]]) d[S] = Num; else ++v[d[now] = dmin];
    return Max - Rest;
}

int main() {
    
    freopen("pvz.in", "r", stdin);
    freopen("pvz.out", "w", stdout);
    
    Init();
    MakeGraph();
    memset(d, 0, sizeof(d)); memset(v, 0, sizeof(v)); v[0] = Num;
    while (d[S] < Num) ans -= aug(S, oo);

    cout << ans << endl;

    return 0;

}

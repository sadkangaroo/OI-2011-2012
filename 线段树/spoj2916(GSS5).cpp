#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 10000 + 5, MaxSize = MaxN * 4;

#define lc (now * 2)
#define rc (now * 2 + 1)
#define cv 1, 1, N
#define UpdateAns ans = max(ans, sum - lside - rside)
#define Lside lside = ((a > b)? 0: min(0, Query(1, 1, N).lmin))
#define Rside rside = ((a > b)? 0: min(0, Query(1, 1, N).rmin))

int T, N, M, pos, x, a, b, sum, lside, rside, ans;

struct Node {
    int s, ls, rs, ms , lmin, rmin;
    Node() {}
    Node(int _s, int _ls, int _rs, int _ms, int _lmin, int _rmin):
      s(_s), ls(_ls), rs(_rs), ms(_ms), lmin(_lmin), rmin(_rmin) {}
}st[MaxSize];

void Update(Node &t, const Node &tl, const Node &tr) {
     t.s = tl.s + tr.s;
     t.ls = max(tl.ls, tl.s + tr.ls);
     t.lmin = min(tl.lmin, tl.s + tr.lmin);
     t.rs = max(tr.rs, tr.s + tl.rs);
     t.rmin = min(tr.rmin, tr.s + tl.rmin);
     t.ms = max(max(tl.ms, tr.ms), tl.rs + tr.ls);
}

void Insert(int now, int l, int r) {
     if (l == r) {st[now] = Node(x, x, x, x, x, x); return;}
     int mid = (l + r) >> 1;
     if (pos <= mid) Insert(lc, l, mid);
     else Insert(rc, mid + 1, r);
     Update(st[now], st[lc], st[rc]);
}

Node Query(int now, int l, int r) {
     if (a <= l && b >= r) return st[now];
     int mid = (l + r) >> 1;
     if (b <= mid) return Query(lc, l, mid);
     if (a > mid) return Query(rc, mid + 1, r);
     Node ret, t1 = Query(lc, l, mid), t2 = Query(rc, mid + 1, r);
     Update(ret, t1, t2); return ret;
}

int main() {

    scanf("%d", &T);
    while (T--) {
          scanf("%d", &N);
          for (pos = 1; pos <= N; ++pos)
              scanf("%d", &x), Insert(cv);
          scanf("%d", &M); int x1, y1, x2, y2;
          for (int i = 0; i < M; ++i) {
              scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
              if (y1 <= x2) {
                 a = x1; b = y2; sum = Query(cv).s;
                 a = x1; b = y1 - 1; Lside; a = x2 + 1; b = y2; Rside; 
                 ans = sum - lside - rside;
              }
              else if (y2 <= y1) {
                      a = x2; b = y2; ans = Query(cv).ms;
                      a = x1; b = y2; sum = Query(cv).s;
                      a = x1; b = x2 - 1; Lside; a = x2 + 1; b = y2; Rside;
                      UpdateAns;
              }
              else {
                   a = x2; b = y1; ans = Query(cv).ms;
                   a = x1; b = y2; sum = Query(cv).s;
                   a = x1; b = x2 - 1; Lside; a = y1 + 1; b = y2; Rside;
                   UpdateAns;
                   a = x1; b = y1; sum = Query(cv).s;
                   a = x1; b = x2 - 1; Lside; a = x2 + 1; b = y1; Rside;
                   UpdateAns;
                   a = x2; b = y2; sum = Query(cv).s;
                   a = x2; b = y1 - 1; Lside; a = y1 + 1; b = y2; Rside;
                   UpdateAns;
              }
              printf("%d\n", ans);
          }
    }

    return 0;

}

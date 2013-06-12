#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 50000 + 5, MaxSize = MaxN * 4;

#define lc (now * 2)
#define rc (now * 2 + 1)

int N, M, pos, x, a, b;

struct Node {
    int s, ls, rs, ms;
    Node() {}
    Node(int _s, int _ls, int _rs, int _ms): s(_s), ls(_ls), rs(_rs), ms(_ms) {}
}st[MaxSize];

void Update(Node &t, const Node &tl, const Node &tr) {
     t.s = tl.s + tr.s;
     t.ls = max(tl.ls, tl.s + tr.ls);
     t.rs = max(tr.rs, tr.s + tl.rs);
     t.ms = max(max(tl.ms, tr.ms), tl.rs + tr.ls);
}

void Insert(int now, int l, int r) {
     if (l == r) {st[now] = Node(x, x, x, x); return;}
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

    scanf("%d", &N);
    for (pos = 1; pos <= N; ++pos)
        scanf("%d", &x), Insert(1, 1, N);
    scanf("%d", &M); int o, p, q;
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &o, &p, &q);
        if (o == 0) pos = p, x = q, Insert(1, 1, N);
        else a = p, b = q, printf("%d\n", Query(1, 1, N).ms); 
    }

    return 0;

}

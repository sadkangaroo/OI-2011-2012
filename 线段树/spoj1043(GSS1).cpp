#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 50000 + 5, MaxSize = MaxN * 4;
int N, M, pos, x, a, b;

struct Node {
    int s, ls, rs, cs;
    Node() {}
    Node(int _s, int _ls, int _rs, int _cs): 
      s(_s), ls(_ls), rs(_rs), cs(_cs) {}
}st[MaxSize];

void Update(Node &t, const Node &tl, const Node &tr) {
     t.s = tl.s + tr.s;
     t.ls = max(tl.ls, tl.s + tr.ls);
     t.rs = max(tr.rs, tr.s + tl.rs);
     t.cs = max(max(tl.cs, tr.cs), tl.rs + tr.ls);
}

void Insert(int now, int l, int r) {
     if (l == r) {st[now] = Node(x, x, x, x); return;}
     int mid = (l + r) >> 1;
     if (pos <= mid) Insert(now * 2, l, mid); 
     else Insert(now * 2 + 1, mid + 1, r);
     Update(st[now], st[now * 2], st[now * 2 + 1]);
}

Node Query(int now, int l, int r) {
    if (a <= l && b >= r) {return st[now];}
    int mid = (l + r) >> 1;
    if (b <= mid) return Query(now * 2, l, mid);
    if (a > mid) return Query(now * 2 + 1, mid + 1, r);
    Node tl = Query(now * 2, l, mid), tr = Query(now * 2 + 1, mid + 1, r);
    Node ret; Update(ret, tl, tr); return ret;
}

int main() {

    scanf("%d", &N);
    for (pos = 1; pos <= N; ++pos)
        scanf("%d", &x), Insert(1, 1, N);
    scanf("%d", &M);
    for (int i = 1; i <= M; ++i)
        scanf("%d%d", &a, &b), printf("%d\n", Query(1, 1, N).cs);

    return 0;

}

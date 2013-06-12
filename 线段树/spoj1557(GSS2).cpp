#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN  = 100000 + 5, MaxSize =MaxN * 4;
const int MaxScore = 100000 * 2 + 5, MaxM = 100000 + 5, HashDelta = 100000;

#define root st[now]
#define lc st[now * 2]
#define rc st[now * 2 + 1]

struct Node {
    int d, hd, ms, hms;
    Node() {d = hd = ms = hms = 0;}
    Node(int _d, int _hd, int _ms, int _hms):
      d(_d), hd(_hd), ms(_ms), hms(_hms) {};
}st[MaxSize];

struct Seg {
    int a, b, id;
    Seg() {}
    Seg(int _a, int _b, int _id):
      a(_a), b(_b), id(_id) {}
    bool operator < (const Seg &t)const {return b < t.b;}
}Q[MaxM];

int N, M, a, b, cnt, delta;
int score[MaxN], last[MaxN], hash[MaxScore], ans[MaxM];

void Update(Node &t, const Node &tl, const Node &tr) {
     t.ms = max(tl.ms + tl.d, tr.ms + tr.d);
     t.hms = max(max(tl.hms, tr.hms), max(tl.ms + tl.hd, tr.ms + tr.hd));
}

void PushDown(Node &t, Node &tl, Node &tr) {
    tl.hd = max(tl.d + t.hd, tl.hd); tl.d += t.d; 
    tr.hd = max(tr.d + t.hd, tr.hd); tr.d += t.d;
    t.d = t.hd = 0;
}

void Insert(int now, int l, int r) {
    if (a <= l && b >= r) {
       root.d += delta;
       root.hd = max(root.hd, root.d);   
       return;
    }
    PushDown(root, lc, rc);
    int mid = (l + r) >> 1;
    if (a <= mid) Insert(now * 2, l, mid);
    if (b >= mid + 1) Insert(now * 2 + 1, mid + 1, r);
    Update(root, lc, rc);
}

int Query(int now, int l, int r) {
    if (a <= l && b >= r) return max(root.hms, root.ms + root.hd);
    PushDown(root, lc, rc);
    int mid = (l + r) >> 1, ret = 0;
    if (a <= mid) ret = max(ret, Query(now * 2, l, mid));
    if (b >= mid + 1) ret = max(ret, Query(now * 2 + 1, mid + 1, r));
    Update(root, lc, rc);
    return ret;
}

int main() {
    
    scanf("%d", &N);
    memset(hash, 0, sizeof(hash));
    for (int i = 1; i <= N; ++i) {
        scanf("%d", score + i);
        last[i] = hash[score[i] + HashDelta];
        hash[score[i] + HashDelta] = i;
    }
    scanf("%d", &M); int x, y;
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &x, &y);
        Q[i] = Seg(x, y, i);
    }
    sort(Q, Q + M);
    cnt = 0;
    for (int i = 0; i < M; ++i) {
        while (cnt + 1 <= Q[i].b) {
              cnt++; a = last[cnt] + 1; b = cnt;
              delta = score[cnt]; Insert(1, 1, N);
        }
        a = Q[i].a; b = Q[i].b; ans[Q[i].id] = Query(1, 1, N);
    }
    for (int i = 0; i < M; ++i) printf("%d\n", ans[i]);

    return 0;

}

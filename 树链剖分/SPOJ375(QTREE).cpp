/*
SPOJ 375 QTREE 树链剖分+LCA+线段树 O(NLogN + Q × Log ^2 N)
给出一棵树，以及两个操作:修改一条边的边权或询问节点a到b的路径上的最大边权
——>树链剖分，将一棵树进行链剖分，使得每个节点属于且仅属于一条链，
可以证明，当进行轻重边剖分时，任意一个节点到根节点跳链次数为O(LogN)
LCA的预处理是O(NlogN)，树链剖分的以及对于每条链建立线段树的预处理是O(N)的
对于询问操作：先求LCA，再对两条路径分别求解最后取max。
在每条路径上，跳链O(LogN)，每条链上线段数操作O(LogN)，总的是O(Log ^2 N);
对于修改操作：先找到待修改边属于的链，再对其线段树进行修改，复杂度为O(LogN)。 
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<iterator>
#include<algorithm>

using namespace std;

#define CV(p) ST.buf + root[p], 1, 1, length[p]
#define LC(p) (p << 1)
#define RC(p) ((p << 1) + 1)
#define Left st, LC(p), l, mid
#define Right st, RC(p), mid + 1, r

const int Max_N = 10005, Max_K = 15;
const int oo = 0x7fffffff;

int T, N, a, b, c, e, idx[Max_N];

struct _ST {
       
    int buf[Max_N * 4],cbuf;

    void Reset() {cbuf = 0;}
   
    int New_ST (int len) {
        cbuf += len * 4;
        return cbuf - len * 4;
    }
    
    void Fix (int *st, int p, int l, int r, int pos, int x) {
        if (l == r) {st[p] = x; return;}
        int mid = (l + r) >> 1;
        if (pos <= mid) Fix(Left, pos, x);
            else Fix(Right, pos, x);
        st[p] = max(st[LC(p)], st[RC(p)]);
    }
    
    int Get_Max (int *st, int p, int l, int r, int ll, int rr) {
        if (ll <= l && rr >= r) return st[p];
        int res = -oo, mid = (l + r) >> 1;
        if (ll <= mid) res = max(res, Get_Max(Left, ll, rr));
        if (rr >= mid + 1) res = max(res, Get_Max(Right, ll, rr));
        return res;
    }

}ST;

struct _Tree {
    
    bool vis[Max_N];
    int size[Max_N], depth[Max_N], weight[Max_N], f[Max_N][Max_K];
    int root[Max_N * 4], length[Max_N], belong[Max_N], pos[Max_N];
    
    struct node {
        int to, d, w;
        node() {}
        node(int _to, int _d, int _w) : to(_to), d(_d), w(_w) {};
    }; typedef vector<node> :: iterator vit; vector<node> g[Max_N];
    
    void Reset() {for (int i = 1; i <= N; ++i) g[i].clear();}

    void Push_Edge(int a, int b, int t, int c) {
        g[a].push_back(node(b, t, c));
        g[b].push_back(node(a, t, c));
    } 

    void GoUp(int &p, int del) {
        for (int k = 0; k < Max_K; k++)
            if (del & (1 << k))
                p = f[p][k];
    }
 
    int LCA(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        GoUp(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int k = Max_K-1; k >= 0; k--)
            if (f[a][k] != f[b][k])
               a = f[a][k], b = f[b][k];
        return f[a][0];        
    }
    
    void Dfs(int p) {
        vis[p] = true;
        for (int k = 1; k < Max_K; ++k)
            f[p][k] = f[f[p][k - 1]][k - 1];
        size[p] = 1;
        for (vit iter = g[p].begin(); iter != g[p].end(); ++iter) 
            if (!vis[iter->to]) {
                depth[iter->to] = depth[p] + 1;
                weight[iter->to] = iter->w;
                idx[iter->d] = iter->to;
                f[iter->to][0] = p;
                Dfs(iter->to);
                size[p] += size[iter->to]; 
            }
    }

    void Divide(int p, int len) {
        vis[p] = true;
        int maxsize=0,q;
        for (vit iter = g[p].begin(); iter != g[p].end(); ++iter)
            if (!vis[iter->to] && size[iter->to] > maxsize)
                maxsize = size[iter->to], q = iter->to;
        if (!maxsize) {
            int st = p;
            for (int i = 1; i < len; ++i) st = f[st][0];
            length[st] = len;
            root[st] = ST.New_ST(len);
            for (int i = len; i; --i) {
                pos[p] = i;
                belong[p] = st;
                ST.Fix(CV(st), i, weight[p]);
                p = f[p][0];
            } 
            return;
        }
        Divide(q, len + 1);
        for (vit iter= g[p].begin(); iter != g[p].end(); ++iter)
            if (!vis[iter->to] && iter->to != q)
                Divide(iter->to, 1);
    }
    
    void Construct() {
        memset(f, 0, sizeof(f));
        memset(vis, false, sizeof(vis));
        depth[1] = 0; Dfs(1);
        weight[1]=-oo;
        memset(vis, false, sizeof(vis));
        ST.Reset(); Divide(1,1);
    }
    
    int Query(int a, int b) {
        if (a == b) return -oo;
        int res = -oo;
        while (a != b) {
            if (belong[a] != belong[b]) {
                res = max(res, ST.Get_Max(CV(belong[b]), 1, pos[b]));
                b = f[belong[b]][0];
            } 
            else {
                res = max(res, ST.Get_Max(CV(belong[b]), pos[a] + 1, pos[b]));
                break;
            }
        }
        return res;
    }
    
    void Change(int p, int c) {ST.Fix(CV(belong[p]), pos[p], c);}
    
}Tree;

void Initial() {
    scanf("%d", &N);
    Tree.Reset();
    for (int i = 1; i < N; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        Tree.Push_Edge(a, b, i, c);
    }
    Tree.Construct();
}

char GetOrder() {
    char res, ch;
    while (ch = getchar(), !(ch >= 'A' && ch <= 'Z'));
    res = ch;
    while (ch = getchar(), ch >= 'A' && ch <= 'Z');
    return res;
}

void Operation() {
    char ch;
    while ( ch = GetOrder(), ch != 'D') {
        if (ch == 'Q') {
            scanf("%d%d", &a, &b);
            c = Tree.LCA(a, b);
            printf("%d\n", max(Tree.Query(c, a), Tree.Query(c, b)));
        } else {
              scanf("%d%d", &e, &c);
              Tree.Change(idx[e], c);
          }
    }
}

int main() {

    scanf("%d", &T);
  
    while (T--) {
        Initial();
        Operation();
    }

    return (0-0);

}

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>

using namespace std;

#define lc(x) (x * 2)
#define rc(x) (x * 2 + 1)
#define mid ((l + r) / 2)

const int MaxM = 100005;
const int MaxN = 1005;
enum {SAVE, LOAD, PAINT};

int N, K, M, a, b, o;
bool t;
int save[MaxM], load[MaxM];
char buf[10];
int command[MaxM];

struct rec {
    int xa, ya, xb, yb, c, id;
    rec() {}
    rec(int _xa, int _ya, int _xb, int _yb, int _c, int _id) :
        xa(_xa), ya(_ya), xb(_xb), yb(_yb), c(_c), id(_id) {}
    bool operator < (const rec &t)const {return id > t.id;}
}paint[MaxM], u;
vector<rec> getin[MaxN], getout[MaxN];

set<rec> st[2][MaxN * 4];

void Init() {
    scanf("%d%d%d", &N, &K, &M);
    int xa, ya, xb, yb, c, x, s = 0;
    memset(save, 0, sizeof(save));
    memset(load, 0, sizeof(load));
    for (int i = 1; i <= M; ++i) {
        scanf("%s", buf);
        switch(*buf) {
            case 'P' : 
                command[i] = PAINT;
                scanf("%d%d%d%d%d", &c, &xa, &ya, &xb, &yb);
                xa++; ya++; xb++; yb++;
                paint[i] = rec(xa, ya, xb, yb, c, i);
                break;
            case 'S' : command[i] = SAVE; save[i] = ++s; break;
            case 'L' : command[i] = LOAD; scanf("%d", &x); load[i] = x; break;  
        }
    }
    rec u; int t;
    for (int i = M; i >= 1; --i) {
        switch(command[i]) {
            case PAINT :
                u = paint[i];
                getin[u.xa].push_back(u);
                getout[u.xb + 1].push_back(u);
                break;
            case LOAD :
                t = load[i];
                while(save[i] != t) i--;
                break;
        }
    }
}

void modify(int p, int l, int r) {
    if (a > r || b < l) return;
    if (a <= l && b >= r) {
        if (t) st[o][p].insert(u); 
            else st[o][p].erase(u);
        return;
    }
    modify(lc(p), l, mid);
    modify(rc(p), mid + 1, r); 
}

int query(int p, int l, int r) {
    int ret = -1;
    if (a < l || a > r) return ret;
    if (!st[o][p].empty()) ret = max(ret, st[o][p].begin()->id);
    if (l == r) return ret;
    ret = max(ret, query(lc(p), l, mid));
    ret = max(ret, query(rc(p), mid + 1, r));
    return ret;
}

void Solve() {
    int ans;
    for (int i = 1; i <= N; ++i) {
        for (int k = 0; k < getin[i].size(); ++k) {
            u = getin[i][k];
            a = u.ya; b = u.yb; t = true; o = (u.xa + u.ya) % 2;
            modify(1, 1, N);
        }
        for (int k = 0; k < getout[i].size(); ++k) {
            u = getout[i][k];
            a = u.ya; b = u.yb; t = false; o = (u.xa + u.ya) % 2;
            modify(1, 1, N);            
        }
        for (int j = 1; j <= N; ++j) {
            a = j; o = (i + a) % 2;
            ans = query(1, 1, N);
            printf("%d ", ans == -1 ? 1 : paint[ans].c);
        }
        puts("");
    }
}

int main() {

    Init();
    Solve();

    return (0-0);

}

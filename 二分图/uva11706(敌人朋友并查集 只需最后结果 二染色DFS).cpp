#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

const int Max_N = 105, Max_M = 1005;

typedef pair<int, int> pii;

bool f;
int N, M;
int a[Max_N][Max_N], col[Max_N][Max_N];
vector<int> g[Max_N];
vector<pii> e;

void Init() {
    int xi, yi;
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= N; ++i) 
        g[i].clear();
    e.clear();
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d", &xi, &yi);
        xi++; yi++;
        a[xi][yi] = a[yi][xi] = 1;
        g[xi].push_back(yi); g[yi].push_back(xi);
        e.push_back(make_pair(xi, yi));
    } 
}

void Dfs(int x, int y, int c) {
    if (col[x][y] != -1 && col[x][y] != c) {
        f = false; return;
    }
    if (col[x][y] == c) return;
    col[x][y] = col[y][x] = c;
    int t;
    for (int i = 0; i < g[x].size(); ++i) {
        t = g[x][i];
        if (t == y) continue;
        if (a[t][y]) Dfs(x, t, c);
            else Dfs(x, t, 1 - c);
        if(!f) return;
    }
    for (int i = 0; i < g[y].size(); ++i) {
        t = g[y][i];
        if (t == x) continue;
        if (a[t][x]) Dfs(y, t, c);
            else Dfs(y, t, 1 - c);
        if(!f) return;
    }    
}

void Solve() {
    f = true;
    memset(col, -1, sizeof(col));
    int tx, ty;
    for (int i = 0; f && (i < e.size()); ++i) {
        tx = e[i].first; ty = e[i].second;
        if (col[tx][ty] != -1) continue;
        Dfs(tx, ty, 0);
    }
    if (f) puts("YES");
        else puts("NO");
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    while (scanf("%d%d", &N, &M) && N) {
        Init();
        Solve();
    }

    return (0-0);

}

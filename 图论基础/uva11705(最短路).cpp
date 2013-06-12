#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

const int MaxN = 55, MaxM = 55;
const int oo = 0x7fffffff;

struct node{
    int x, y, d;
    node() {}
    node(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {}
    bool operator > (const node &t)const {return d > t.d;}
}; priority_queue< node, vector<node>, greater<node> > q;

int N, M;
vector<node> g[MaxN][MaxM];
int d[MaxN][MaxM], dir[MaxN][MaxM];
bool done[MaxN][MaxM];


bool check(int i, int j) {return (i >= 1 && i <= N && j >= 1 && j <= M);}

void Init() {
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            g[i][j].clear();
    int x;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j) {
            scanf("%d", &x);
            if(x == 0) continue;
            if(check(i - x, j)) g[i - x][j].push_back(node(i, j, 3)); 
            if(check(i + x, j)) g[i + x][j].push_back(node(i, j, 0)); 
            if(check(i, j - x)) g[i][j - x].push_back(node(i, j, 2)); 
            if(check(i, j + x)) g[i][j + x].push_back(node(i, j, 1));
        }   
}

void Dij() {
    memset(dir, -1, sizeof(dir));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            d[i][j] = oo;
    memset(done, false, sizeof(done));
    d[1][1] = 0;
    q.push(node(1, 1, 0));
    node t; int fx, fy, tx, ty, td;
    while (!q.empty()) {
        t = q.top(); q.pop();
        fx = t.x; fy = t.y;
        if (done[fx][fy]) continue;
        done[fx][fy] = true;
        vector<node> &now = g[fx][fy];
        for (int i = 0; i < now.size(); ++i) {
            tx = now[i].x; ty = now[i].y; td = now[i].d;
            if (d[fx][fy] + 1 < d[tx][ty] || 
                d[fx][fy] + 1 == d[tx][ty] && td > dir[tx][ty]) {
                    d[tx][ty] = d[fx][fy] + 1;
                    dir[tx][ty] = td;
                    q.push(node(tx, ty, d[tx][ty])); 
            }
        }
    }
}

void Ans() {
    for (int i = 1; i <= N; ++i) { 
        for (int j = 1; j <= M; ++j)
            if (i == 1 && j == 1) putchar('*');
                else switch(dir[i][j]) {
                         case -1 : putchar('X'); break;
                         case 0 : putchar('S'); break;
                         case 1 : putchar('E'); break;
                         case 2 : putchar('W'); break;
                         case 3 : putchar('N'); break;
                     }
        puts("");
    } 
    puts("");
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    while (scanf("%d%d", &N, &M) && N) {
        Init();
        Dij();
        Ans();
    }

    return (0-0);

}

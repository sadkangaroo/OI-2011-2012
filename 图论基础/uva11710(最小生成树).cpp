#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<string>
using namespace std;

const int MaxN = 405, MaxM = 79805, MaxL = 15;

map<string, int> Station;

int N, M;
char s[MaxL];

struct Edge {
    int a, b, v;
    Edge() {}
    Edge(int _a, int _b, int _v) : a(_a), b(_b), v(_v) {}
    bool operator < (const Edge &t)const {return v < t.v;}
}e[MaxM]; int top;

void Init() {
    Station.clear();
    for (int i = 1; i <= N; ++i) {
        scanf("%s", s);
        Station[(string)s] = i;
    }
    top = 0; int a, b, v;
    for (int i = 1; i <= M; ++i) {
        scanf("%s", s); a = Station[(string)s];
        scanf("%s", s); b = Station[(string)s];
        scanf("%d", &v);
        e[top++] = Edge(a, b, v);
    }
    sort(e, e + top);
    scanf("%s", s);
} 

int fa[MaxN];

int Grand(int x) {
    if (fa[x] == x) return x;
    fa[x] = Grand(fa[x]);
    return fa[x];
}

void Solve() {
    int ans = 0, sum = 0;
    for (int i = 1; i <= N; ++i) fa[i] = i;
    Edge u; int fx, fy;
    for (int i = 0; i < top; ++i) {
        u = e[i];
        fx = Grand(u.a); fy = Grand(u.b);
        if(fx == fy) continue;
        sum++; ans += u.v;
        fa[fx] = fy;        
    }
    if (sum == N - 1) printf("%d\n", ans);
        else puts("Impossible");
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    
    while (scanf("%d%d", &N, &M) && N) {
        Init();
        Solve();
    }
    
    return 0;

}

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MaxN = 15, MaxM = 15;
const int HashSize = 1 << 16, Mod = HashSize - 1;
typedef long long LL;
typedef pair<int, LL> pii;

LL ans;
int N, M, LastI, LastJ, now, key;
char a[MaxN][MaxM];
pii f[2][HashSize], t;

void Init() {
    memset(a, 0, sizeof(a));
    scanf("%d%d ", &N, &M);
    for (int i = 0; i < N; ++i) {
        gets(a[i]);
        for (int j = 0; j < M; ++j)
            if (a[i][j] == '.')
                LastI = i, LastJ = j;
    }
}

inline int GetPlug(int s, int p) {return (s >> ((M - p) << 1)) & 3;}

inline int Delta(int x, int p) {return x << ((M - p) << 1);}

inline int HashIt(int x) {return (x ^ (x >> 3) ^ (x >> 7) ^ (x >> 10)) & Mod;}

inline void Update(pii t) {
    key = HashIt(t.first);
    while (f[now][key].first != -1 && f[now][key].first != t.first)
        key = (key + 1) & Mod;
    if (f[now][key].first == -1) f[now][key] = t;
        else f[now][key].second += t.second; 
}

void UpdateIt(int x, int y) {
    now ^= 1;
    for (int i = 0; i < HashSize; ++i)
        f[now][i] = pii(-1, 0);
    int p, q, s, r, o;
    for (int k = 0; k < HashSize; ++k) {
        if (!f[now ^ 1][k].second) continue;
        t = f[now ^ 1][k];
        if (!y) t.first >>= 2;
        p = GetPlug(t.first, y); q = GetPlug(t.first, y + 1);
        if (a[x][y] == '*') {
            t.first -= (Delta(p, y) + Delta(q, y + 1));
            Update(t);
        }
        else if (!p && !q) {
                 if (a[x + 1][y] == '.' && a[x][y + 1] == '.') {
                     t.first += (Delta(1, y) + Delta(2, y + 1));
                     Update(t);
                 }
             }
        else if (!p && q) {
                 if (a[x][y + 1] == '.') Update(t);
                 if (a[x + 1][y] == '.') {
                     t.first += (Delta(q, y) - Delta(q, y + 1));
                     Update(t);
                 }
             }
        else if (p && !q) {
                 if (a[x + 1][y] == '.') Update(t);
                 if (a[x][y + 1] == '.') {
                     t.first += (Delta(p, y + 1) - Delta(p, y));
                     Update(t);
                 }
             }
        else if (p == 1 && q == 1) {
                 s = 0; r = y + 1;
                 while (s != 1) {
                     o = GetPlug(t.first, ++r);
                     if (o == 1) --s;
                         else if (o == 2) ++s;
                 }
                 t.first -= (Delta(1, y) + Delta(1, y + 1) + Delta(1, r));
                 Update(t);
             }
        else if (p == 2 && q == 2) {
                 s = 0; r = y;
                 while (s != 1) {
                     o = GetPlug(t.first, --r);
                     if (o == 1) ++s;
                         else if (o == 2) --s;
                 }
                 t.first += (Delta(1, r) - Delta(2, y) - Delta(2, y + 1));
                 Update(t);
             }
        else if (p == 2 && q == 1) {
                 t.first -= (Delta(2, y) + Delta(1, y + 1));
                 Update(t);
             }
        else if (p == 1 && q == 2) {
                 if (x == LastI && y == LastJ) 
                     ans += t.second;
             }
    }
}

void Solve() {
    ans = now = 0;
    t = pii(0, 1);
    Update(t);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            UpdateIt(i, j);
    cout << ans << endl;
}

int main() {

    Init();
    Solve();
    
    return 0;

}

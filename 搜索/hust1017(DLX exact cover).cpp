#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MaxN = 1005, MaxM = 1005, MaxC = 105, Total = MaxN * MaxC;
const int oo = 0x7fffffff;

#define Lab(a, b) (a * M + b)

int N, M, h, ans, buf;
int lx[MaxN][MaxC], ly[MaxM][MaxC], plx[MaxN], ply[MaxM], O[MaxN];
int L[Total], R[Total], U[Total], D[Total], C[Total], row[Total];

void Init() {
    buf = M;     
    memset(plx, 0, sizeof(plx));
    memset(ply, 0, sizeof(ply));
    for (int x = 1; x <= N; ++x) {
        int c, y;
        scanf("%d", &c);
        while (c--) {
            scanf("%d", &y); 
            lx[x][plx[x]++] = ly[y][ply[y]++] = ++buf;
            C[buf] = y; row[buf] = x;
        }
    }
    int a, b;
    for (int x = 1; x <= N; ++x)
        for (int k = 0; k < plx[x]; ++k) {
            a = lx[x][k]; b = lx[x][(k + 1) % plx[x]];
            R[a] = b; L[b] = a;
        }
    for (int y = 0; y <= M; ++y) {
        R[y] = (y + 1) % (M + 1); 
        L[(y + 1) % (M + 1)] = y;
    }
    for (int y = 1; y <= M; ++y) {
        for (int k = 0; k < ply[y] - 1; ++k) {
            a = ly[y][k]; b = ly[y][k + 1];
            D[a] = b; U[b] = a;
        }
        if (ply[y]) {
            U[ly[y][0]] = y; D[y] = ly[y][0];
            D[ly[y][ply[y] - 1]] = y; U[y] = ly[y][ply[y] - 1];
        }
        else D[y] = U[y] = y;
    }           
}

void remove(int c) {
    L[R[c]] = L[c]; R[L[c]] = R[c];
    for (int x = D[c]; x != c; x = D[x])
        for (int y = R[x]; y != x; y = R[y]) 
            U[D[y]] = U[y], D[U[y]] = D[y], ply[C[y]]--;
}

void resume(int c) {
    for (int x = U[c]; x != c; x = U[x])
        for (int y = L[x]; y != x; y = L[y]) 
            U[D[y]] = y, D[U[y]] = y, ply[C[y]]++;
    L[R[c]] = c; R[L[c]] = c;
}

bool Dfs(int k) {
    if (R[h] == h) {ans = k - 1; return true;}
    int s = oo, c;
    for (int y = R[h]; y != h; y = R[y])
        if (ply[y] < s) s = ply[y], c = y;
    remove(c);
    for (int x = D[c]; x != c; x = D[x]) {
        O[k] = row[x];
        for (int y = R[x]; y != x; y = R[y]) remove(C[y]);
        if (Dfs(k + 1)) return true;
        for (int y = L[x]; y != x; y = L[y]) resume(C[y]);
    }
    resume(c);
    return false;
}

void Solve() {
    h = ans = 0;
    if (Dfs(1)) {
        printf("%d", ans);
        for (int i = 1; i <= ans; ++i)
            printf(" %d", O[i]);
        puts("");
    }
    else puts("NO");
}

int main() {
    
    while (scanf("%d%d", &N, &M) != EOF) {
        Init();
        Solve();
    }
    
    return 0;

}

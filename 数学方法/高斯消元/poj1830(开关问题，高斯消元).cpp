#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const double eps = 1e-7;
const int MaxN = 35;

int K, N, ans;

bool mat[MaxN][MaxN];

void Init() {
    scanf("%d", &N);
    memset(mat, 0, sizeof(mat));
    int x, a, b;
    for (int i = 0; i < N; ++i) 
        scanf("%d", &x), mat[i][N] ^= x;
    for (int i = 0; i < N; ++i) 
        scanf("%d", &x), mat[i][N] ^= x;
    for (int i = 0; i < N; ++i) mat[i][i] = 1;
    while (scanf("%d%d", &a, &b) && a) 
        a--, b--, mat[b][a] = 1;
}


int Gauss() {
    int i, j, k, p;
    for (i = 0, j = 0; i < N, j < N; ++i, ++j) {
        for (k = i; k < N; ++k) if (mat[k][j]) break;
        if (k == N) {i--; continue;}
        for (p = 0; p <= N; ++p) swap(mat[i][p], mat[k][p]);
        for (k = i + 1; k < N; ++k) if (mat[k][j])
            for (p = 0; p <= N; ++p) mat[k][p] ^= mat[i][p];
    }
    for (k = i; k < N; ++k) if (mat[k][N]) return -1;
    return (N - i);
}

int main() {

    scanf("%d", &K);
    while (K--) {
        Init();
        ans = Gauss();
        if (ans == -1) puts("Oh,it's impossible~!!");
        else printf("%d\n", (int)(pow(2.0, ans) + eps));
    }

    return 0;

}

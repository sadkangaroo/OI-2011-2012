#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 155;
const int oo = 0x7fffffff;

int N;
int g[MaxN][MaxN], mx[MaxN], my[MaxN], lx[MaxN], ly[MaxN];
bool visx[MaxN],  visy[MaxN]; 

void Init() {
    scanf("%d", &N);
    int d;
    memset(g, -1, sizeof(g));
    for (int i = 1; i <= N; ++i) {
        d = 0;
        for (int j = 1; j <= N; ++j) {
            scanf("%d", &g[i][j]);
            if (g[i][j] > d) d = g[i][j];
        }
        lx[i] = d; ly[i] = 0;
    }
}

bool find(int x) {
    visx[x] = true;
    for (int i = 1; i <= N; ++i)
        if (!visy[i] && g[x][i] != -1 && lx[x] + ly[i] == g[x][i]) {
            visy[i] = true;
            if (my[i] == 0 || find(my[i])) {
                mx[x] = i; my[i] = x;
                return true;
            }
        }
    return false;
}

void KM() {
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    int d;
    for (int i = 1; i <= N; ++i)
        if (mx[i] == 0) {
            for (;;) {
                memset(visx, false, sizeof(visx));
                memset(visy, false, sizeof(visy));
                if (find(i)) break;
                d = oo;
                for (int i = 1; i <= N; ++i)
                    for (int j = 1; j <= N; ++j)
                        if (g[i][j] != -1 && visx[i] && !visy[j] 
                            && lx[i] + ly[j] - g[i][j] < d)
                            d = lx[i] + ly[j] - g[i][j];
                for (int i = 1; i <= N; ++i) {
                    !!!!!!!!if (visx[i]) lx[i] += d; 
                    !!!!!!!!if (visy[i]) ly[i] -= d;
                }
            }
        }
}

void Ans() {
    int ans = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            if (j != mx[i]) ans += g[i][j];
    printf("%d\n", ans);
}

int main() {

    Init();
    KM();
    Ans();

    return (0-0);

}

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 1005, MaxM = 1005;

int N, M, K;
bool g[MaxN][MaxM], visy[MaxM];
int mx[MaxN], my[MaxN];

void Init() {
    scanf("%d%d%d", &N, &M, &K);
    int ai, bi;
    memset(g, false, sizeof(g));
    for (int i = 1; i <= K; ++i) 
        scanf("%d%d", &ai, &bi), g[ai][bi] = true;
}

bool find(int x) {
    for (int i = 1; i <= M; ++i)
        if (!visy[i] && g[x][i]) {
            visy[i] = true;
            if (my[i] == 0 || find(my[i])) {
                mx[x] = i; my[i] = x;
                return true;
            }
        }
    return false;
}

void Hungary() {
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    int ans = 0;
    for (int i = 1; i <= N; ++i) 
        if (mx[i] == 0) {
            memset(visy, false, sizeof(visy));
            if (find(i)) ans++;
        }
    printf("%d\n", M + N - ans);
}

int main() {
    
    Init();
    Hungary();

    return (0-0);

}

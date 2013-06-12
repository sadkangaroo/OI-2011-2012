#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 2000 + 30 + 5;

char c;
int N, d; 
bool a[MaxN][MaxN];
int super[MaxN][MaxN];

void Init() {
    scanf("%d ", &N);
    memset(a, false, sizeof(a));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            c = getchar(), a[i][j] = c - '0';
        getchar();
    }
}

void MakeSuperMatrix() {
    memset(super, 0, sizeof(super));
    d = N / 30;
    if (N % 30) d++;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < d; ++j) 
            for (int k = 0; k < 30; ++k)
                super[i][j] |= (a[i][j * 30 + k] << k);    
}

void SuperFloyed() {
    for (int j = 0; j < d; ++j)
        for (int k = 0; k < 30; ++k)
            for (int i = 0; i < N; ++i)
                if (super[i][j] & (1 << k)) 
                    for (int p = 0; p < d; ++p) 
                        super[i][p] |= super[j * 30 + k][p];
                            
    int ans = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < d; ++j)
            for (int k = 0; k < 30; ++k) {
                if (j * 30 + k >= N) continue;
                if (i == j * 30 + k) {ans++; continue;}
                if (super[i][j] & (1 << k)) ans++;
            }
    cout << ans << endl;         
}

int main() {
    
    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);
    
    Init();
    MakeSuperMatrix();
    SuperFloyed();
    
    return 0;

}

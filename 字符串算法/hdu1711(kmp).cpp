#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int MaxN = 1000000 + 5, MaxM = 10000 + 5;

int T, N, M;
int a[MaxN], b[MaxM], Next[MaxM];

void GetNext() {
     Next[1] = 0; int t;
     for (int i = 2; i <= M; ++i) {
         t = Next[i - 1];
         while (t && b[t + 1] != b[i]) t = Next[t];
         if (b[t + 1] == b[i]) Next[i] = t + 1; else Next[i] = 0;
     }
}

int Match() {
    int j = 0; 
    for (int i = 1; i <= N; ++i) {
        while (j && b[j + 1] != a[i]) j = Next[j];
        if (b[j + 1] == a[i]) j++;
        if (j == M) return i - M + 1;
    }
    return -1;
}

int main() {

    scanf("%d", &T);
    while (T--) {
          scanf("%d%d", &N, &M);
          for (int i = 1; i <= N; ++i) scanf("%d", a + i);
          for (int i = 1; i <= M; ++i) scanf("%d", b + i);
          GetNext();
          printf("%d\n", Match());
    }   

    return 0;
}

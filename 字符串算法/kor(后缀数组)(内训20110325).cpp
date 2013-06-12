#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>

using namespace std;

const int MaxN = 200000 + 5, MaxLen = MaxN * 2 + 5;
const int MaxKey = MaxN * 2 + 5, MaxP = 20;;

int N, Len, MaxNum, rmqk;
int SA[MaxLen], tmp[MaxLen], log2N[MaxLen];
int a[MaxLen * 2], rank[MaxLen * 2], tmp2[MaxLen * 2], height[MaxLen];
int hash[MaxKey], f[MaxLen][MaxP], head[MaxLen], t, ans[MaxLen], t2;

void Init() {
     scanf("%d", &N);
     memset(a, 0, sizeof(a));
     for (int i = 1; i <= N; ++i) scanf("%d", a + i);
     a[N + 1] = N + 1;
     Len = 2 * N + 1;
     for (int i = N + 2, j = N; i <= Len, j >= 1; ++i, --j) a[i] = a[j]; 
     for (int i = 1; i <= Len; ++i) log2N[i] = (int)(log(i) / log(2));
}

void RadixSort(int *key) {
     memset(hash, 0, sizeof(hash));
     for (int i = 1; i <= Len; ++i) hash[key[i]]++;
     for (int i = 1; i < MaxKey; ++i) hash[i] += hash[i - 1];
     for (int i = Len; i >= 1; --i) SA[hash[key[tmp[i]]]--] = tmp[i];
}

void GetSA() {
     if (Len == 1) {SA[1] = rank[1] = 1; return;}
     for (int i = 1; i <= Len; ++i) tmp[i] = i;
     memcpy(rank, a, sizeof(rank)); RadixSort(rank);
     for (int k = 1; k < Len; k <<= 1) {                     
         RadixSort(rank + k); memcpy(tmp + 1, SA + 1, Len * 4); 
         RadixSort(rank); memcpy(tmp2 + 1, rank + 1, 2 * Len * 4);
         for (int i = 1, p = 1; i <= Len; ++i) {
             rank[SA[i]] = p;
             if (tmp2[SA[i]] != tmp2[SA[i + 1]] 
                || tmp2[SA[i] + k] != tmp2[SA[i + 1] + k]) p++;
         }
     }
}

void GetHeight() {
     int i, j, p = 0; height[1] = 0;
     for (i = 1; i <= Len; ++i) {
         if (p) p--; if (rank[i] == 1) continue;
         j = SA[rank[i] - 1];
         while (a[i + p] == a[j + p]) p++;
         height[rank[i]] = p;
     }
}

void RMinQ_Init() {
     for (int i = 1; i <= Len; ++i) f[i][0] = height[i];
     for (int k = 1; (1 << k) <= Len; ++k)
         for (int i = 1; i + (1 << k) - 1 <= Len; ++i)
             f[i][k] = min(f[i][k - 1], f[i + (1 << (k - 1))][k - 1]);
}

int RMinQ(int p1, int p2) {
    rmqk = log2N[p2 - p1 + 1];
    return min(f[p1][rmqk], f[p2 - (1 << rmqk) + 1][rmqk]);
}

int LCP(int x, int y) {
    if (rank[x] > rank[y]) return RMinQ(rank[y] + 1, rank[x]);
    return RMinQ(rank[x] + 1, rank[y]);
}

bool cmp(int x, int y) {return rank[x] < rank[y];}

void check(int K) {
     t = 0;
     for (int i = 1; i + K - 1 <= N; i += K) {
         head[t++] = i;
         head[t++] = Len - i - K + 2;
     }
     sort(head, head + t, cmp);
     int tot = 0;
     for (int i = 0; i < t; ++i) {
         if (LCP(head[i], Len - head[i] - K + 2) >= K) tot += 2;
         else tot++;
         while (i + 1 < t && LCP(head[i], head[i + 1]) >= K) i++;
     }
     tot >>= 1;
     if (tot > MaxNum) MaxNum = tot, t2 = 0;
     if (tot == MaxNum) ans[t2++] = K;
}

int main() {

    freopen("kor.in", "r", stdin);
    freopen("kor.out", "w", stdout);

    Init();
    GetSA();
    GetHeight();
    
    RMinQ_Init();
    MaxNum = t2 = 0;
    for (int i = 1; i <= N; ++i) check(i);

    printf("%d %d\n", MaxNum, t2);
    for (int i = 0; i < t2; ++i) {
        if (i) putchar(' ');
        printf("%d", ans[i]);
    }
    puts("");

    return 0;

}

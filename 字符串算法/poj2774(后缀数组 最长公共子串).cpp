#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

#define eq1 (tmp2[SA[i]] == tmp2[SA[i + 1]])
#define eq2 (tmp2[SA[i] + k] == tmp2[SA[i + 1] + k])

const int MaxLen = 100000 * 4 + 10, MaxK = 20, MaxKey = 100000 * 4 + 10;

char s[MaxLen], stmp[MaxLen];
int SA[MaxLen], rank[MaxLen], height[MaxLen];
int tmp[MaxLen], tmp2[MaxLen], hash[MaxLen], f[MaxLen][MaxK];
int len, ltmp;

void Init() {
    strcpy(s, "$");
    gets(stmp); ltmp = strlen(stmp); strcat(s, stmp);
    strcat(s, "$");
    gets(stmp); strcat(s, stmp);
    len = strlen(s) - 1;
}

void RadixSort(int *key) {
    memset(hash, 0, sizeof(hash));
    for (int i = 1; i <= len; ++i) hash[key[i]]++;
    for (int i = 1; i < MaxKey; ++i) hash[i] += hash[i - 1];
    for (int i = len; i >= 1; --i) SA[hash[key[tmp[i]]]--] = tmp[i];
}

void GetSA() {
    memset(rank, 0, sizeof(rank));
    for (int i = 1; i <= len; ++i) tmp[i] = i;
    for (int i = 1; i <= len; ++i) 
        rank[i] = (s[i] == '$' ? 27 : s[i] - 'a' + 1);
    RadixSort(rank);
    for (int k = 1; k <= len; k <<= 1) {
        RadixSort(rank + k); 
        for (int i = 1; i <= len; ++i) tmp[i] = SA[i];
        RadixSort(rank); 
        for (int i = 1; i <= len; ++i) tmp2[i] = rank[i];
        for (int i = 1, p = 1; i <= len; ++i) { 
            rank[SA[i]] = p;
            if (!(eq1 && eq2)) p++;
        }
    } 
}

void GetHeight() {
    int p = 0, j;
    height[1] = 0;
    for (int i = 1; i <= len; ++i) {
        if (p != 0) p--;
        if (rank[i] == 1) continue;
        j = SA[rank[i] - 1];
        while (s[i + p] == s[j + p]) p++;
        height[rank[i]] = p;
    }
}

int main() {

    Init();
    GetSA();
    GetHeight();
    
    int ans = 0;
    for (int i = 2; i <= len; ++i)
        if(SA[i] <= ltmp && SA[i - 1] > ltmp + 1
           || SA[i - 1] <= ltmp && SA[i] > ltmp + 1)
               if (height[i] > ans) ans = height[i];
    printf("%d\n", ans);

    return (0-0);

}

#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int oo = 0x7fffffff;
const int MaxLen = 200 + 5, MaxN = 4000 + 5;

int N, len, CntLen, BestLen, Next[MaxLen], Extend[MaxLen];
char s[MaxN][MaxLen], BestAns[MaxLen], tmp[MaxLen];


void GetNext(char* s) {
     int k = 0, a = 1, j;
     while (s[k] == s[k + 1]) k++; Next[1] = k;
     for (k = 2; s[k]; ++k) {
         if (k + Next[k - a] < a + Next[a]) {Next[k] = Next[k - a]; continue;}
         j = max(a + Next[a] - k, 0);
         while (s[k + j] && s[j] == s[k + j]) ++j;
         Next[k] = j; a = k;
     }
}

void GetExtend(char* s1, char* s2) {
     int k = 0, a = 0, j;
     while (s1[k] && s2[k] && s1[k] == s2[k]) k++; Extend[0] = k;
     for (k = 1; s1[k]; ++k) {
         if (k + Next[k - a] < a + Extend[a]) {Extend[k] = Next[k - a]; continue;}
         j = max(a + Extend[a] - k, 0);
         while (s1[k + j] && s2[j] && s1[k + j] == s2[j]) j++;
         Extend[k] = j; a = k;
     }
}

void ExtendedKMP(char* s1, char* s2) {
     GetNext(s2); GetExtend(s1, s2);
}

int Solve(char *str) {
    int ret = oo, Max;
    for (int i = 2; i <= N; ++i) {
        ExtendedKMP(s[i], str);
        Max = 0;
        for (int j = 0; s[i][j] != '\0'; ++j) Max = max(Max, Extend[j]);
        ret = min(ret, Max);
    }
    return ret;
}

int main() {
    
    while (scanf("%d", &N) && N) {
          BestLen = 0;
          for (int i = 1; i <= N; ++i) scanf(" "), gets(s[i]);
          len = strlen(s[1]);
          for (int i = 0; i < len; ++i) {
              CntLen = Solve(&s[1][i]);
              strncpy(tmp, &s[1][i], CntLen); tmp[CntLen] = '\0';
              if (CntLen > BestLen) BestLen = CntLen, strcpy(BestAns, tmp);
              else if (CntLen && CntLen == BestLen && strcmp(tmp, BestAns) < 0) 
                   strcpy(BestAns, tmp);
          }
          if (!BestLen) puts("IDENTITY LOST");
          else puts(BestAns);
    }
    
    return 0;

}

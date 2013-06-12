#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxLen = 110000 * 2 + 5;

char stmp[MaxLen], s[MaxLen];
int rad[MaxLen], len;

void Manacher(char* s, int len, int* rad) {
     int i = 0, j = 0, k;
     while (i < len) {
           while (i - j >= 0 && i + j + 1 < len 
             && s[i - j] == s[i + j + 1]) j++;
           rad[i] = j;
           for (k = 1; j - k >= 0 && rad[i] - k != rad[i - k]; ++k)
               rad[i + k] = min(rad[i - k], rad[i] - k);
           i += k;
           j = max(0, j - k);
     }
     int ans = 0;
     for (int i = 0; i < len; ++i) ans = max(ans, rad[i]);
     printf("%d\n", ans);
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    while (scanf("%s", stmp) != -1) {
          len = strlen(stmp);
          for (int i = 0; i < len; ++i)
              s[i * 2] = s[i * 2 + 1] = stmp[i];
          len *= 2;
          Manacher(s, len, rad);
    }

    return 0;

}

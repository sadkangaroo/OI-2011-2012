#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MaxL = 10005;
const double eps = 1e-7;

int T, len, n;
char s[MaxL];

int main() {

    scanf("%d%c", &T);
    while (T--) {
        gets(s);
        len = strlen(s);
        n = (int)(sqrt(len) + eps);
        if (n * n != len) puts("INVALID");
        else {
            for (int j = 0; j < n; ++j)
                for (int i = 0; i < n; ++i)
                    putchar(s[i * n + j]);
            puts("");
        }
    }
    
    return 0;

}

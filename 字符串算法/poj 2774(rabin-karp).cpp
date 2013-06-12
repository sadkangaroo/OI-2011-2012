#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

typedef unsigned long long uLL;
typedef pair<uLL, uLL> puu;

const int MaxLen = 100000 + 5;

int l1, l2, t1, t2;
char s1[MaxLen], s2[MaxLen];
uLL h1[MaxLen], h2[MaxLen], p[3][MaxLen];
puu tmp[MaxLen * 2];

void MakeHash(int len, uLL* h, char* s, int k, int l) {
     h[0] = 0;
     for (int i = 0; i < len; ++i) 
         h[0] = h[0] * p[k][1] + s[i];
     for (int i = 1; i + len <= l; ++i)
         h[i] = (h[i - 1] - s[i - 1] * p[k][len - 1]) * p[k][1] + s[i + len - 1];
}

bool check(int len, int k) {
     MakeHash(len, h1, s1, k, l1); MakeHash(len, h2, s2, k, l2);
     t1 = l1 - len + 1; t2 = l2 - len + 1;
     for (int i = 0; i < t1; ++i) tmp[i] = puu(h1[i], 0);
     for (int i = t1; i < t1 + t2; ++i) tmp[i] = puu(h2[i - t1], 1);
     sort(tmp, tmp + t1 + t2);
     for (int i = 0; i < t1 + t2 - 1; ++i) 
         if (tmp[i].first == tmp[i + 1].first)
            if (tmp[i].second != tmp[i + 1].second) return true;
     return false;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    p[0][0] = p[1][0] = p[2][0] = 1; 
    p[0][1] = 1313133; p[1][1] = 1000003; p[2][1] = 999983;
    for (int k = 0; k < 3; ++k)
        for (int i = 2; i < MaxLen; ++i) 
            p[k][i] = p[k][i - 1] * p[k][1];
    gets(s1); gets(s2); l1 = strlen(s1); l2 = strlen(s2);
    int l = 0, r = min(l1, l2), mid;
    while (l != r) {
          mid = (l + r + 1) >> 1;
          if (check(mid, 0) && check(mid, 1) && check(mid, 2)) l = mid;
          else r = mid - 1;
    }
    cout << l << endl;

    return 0;

}

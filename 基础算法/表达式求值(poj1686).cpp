#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<ctime>
using namespace std;

const int MaxLen = 85;

int N, o[256], v[3][256], num[MaxLen];
char s1[MaxLen], s2[MaxLen], ans[MaxLen], stk[MaxLen];

void Convert(char *s) {
    int len = strlen(s), p = 0, q = 0; char c;
    for (int i = 0; i < len; ++i) {
        c = s[i];
        if (isalpha(c) || isdigit(c)) ans[p++] = c;
        if (c == '(') stk[q++] = c;
        if (c == ')') { 
            while (stk[--q] != '(') 
                ans[p++] = stk[q];
        }
        if (c == '+' || c == '-' || c == '*') {
            while (q && o[stk[q - 1]] >= o[c]) 
                ans[p++] = stk[--q];
            stk[q++] = c;
        }
    }
    while (q) ans[p++] = stk[--q];
    ans[p] = '\0';
    strcpy(s, ans);
}

int calc(char *s, int t) {
    int len = strlen(s), q = 0; char c;
    for (int i = 0; i < len; ++i) {
        c = s[i];
        if (isalpha(c) || isdigit(c)) {num[q++] = v[t][c]; continue;}
        q--;
        switch (c) {
            case '+' : num[q - 1] += num[q]; break;
            case '-' : num[q - 1] -= num[q]; break;
            case '*' : num[q - 1] *= num[q]; break;
        }
    }
    return num[0];
}

inline bool Compare(char *s1, char *s2, int t) {
    return calc(s1, t) == calc(s2, t);
}

void Init() {
    scanf("%d ", &N);
    o['('] = 0; o['+'] = o['-'] = 1; o['*'] = 2;
    srand(time(NULL));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 256; ++j)
            if (isdigit(j)) v[i][j] = j - '0';
            else v[i][j] = rand() % 10 + 1;
}

void Solve() {
    for (int i = 1; i <= N; ++i) {
        gets(s1); gets(s2);
        Convert(s1); Convert(s2);
        if (Compare(s1, s2, 0) && Compare(s1, s2, 1) && Compare(s1, s2, 2))
            puts("YES"); else puts("NO");
    }
}

int main() {
    
    Init();
    Solve();
    
    return 0;

}

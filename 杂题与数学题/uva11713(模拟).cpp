#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MaxL = 25;

char s1[MaxL], s2[MaxL], len, len2;
int N;

bool check(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void JudgeIt() {
    for (int i = 0; i < len; ++i)
        if (!(s1[i] == s2[i] || check(s1[i]) && check(s2[i]))) {
            puts("No"); return;
        }
    puts("Yes");
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    
    scanf("%d ", &N);
    while (N--) {
        gets(s1); gets(s2);
        len = strlen(s1); len2 = strlen(s2);
        if (len != len2) puts("No");
            else JudgeIt();
    }
    
    return 0;

}

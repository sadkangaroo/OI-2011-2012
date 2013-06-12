#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int N;
char s[5];

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    
    while (scanf("%d ", &N) && N) {
        printf("5 %d\n", N);
        puts("0 1 1 1 R\n1 0 0 0 L\n1 1 2 1 R\n2 0 3 0 L\n3 1 3 1 L");
        for (int i = 1; i <= N; ++i) {
            gets(s);
            switch (s[0]) {
                case 'T' : puts("1 1"); break;
                case 'M' : puts("2 1"); break;
                case 'A' : puts("3 3"); break;
                case 'W' : puts("3 4"); break;
            }
        }
    }
    
    return 0;

}

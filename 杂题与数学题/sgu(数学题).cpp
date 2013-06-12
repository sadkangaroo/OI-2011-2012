#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long LLd;

LLd N;

void Solve() {
    LLd ans = 0;
    while (ans + (ans + 1LL) * (((1LL) << (ans + 1LL)) - 1LL) < N) {ans++;}
    printf("%I64d\n", ans);
}

int main() {

    scanf("%I64d", &N);
    Solve();

    return (0-0);

}

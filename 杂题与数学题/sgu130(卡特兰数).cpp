#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int Max_N = 35;

typedef long long LLd;

LLd a[Max_N];
int N;

int main() {

    memset(a, 0, sizeof(a));
    a[0] = 1;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j <= N - 1; ++j)
            a[i] += (a[j] * a[i - 1 - j]);
    printf("%I64d %d\n", a[N], N + 1);
    
    
    return (0-0);

}

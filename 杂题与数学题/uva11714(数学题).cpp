#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps = 1e-7;

int N;

int main() {

    while (scanf("%d", &N) != EOF)
        printf("%d\n", N - 1 + (int)(log(N - 1) / log(2) + eps));
    
    return 0;

}

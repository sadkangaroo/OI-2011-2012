#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int Max_N = 1000005;
const int Mod = 1000000;
const double eps = 1e-9;

int n;
int a[Max_N];

void Init() {
    a[0] = 1;
    for (int i = 1; i < Max_N; ++i) {
        a[i] = a[(int)(i - sqrt(i) + eps)]
             + a[(int)(log(i) + eps)]
             + a[(int)(i * sin(i) * sin(i) + eps)];
        if (a[i] > Mod) a[i] -= Mod;
        if (a[i] > Mod) a[i] -= Mod;
    }
    
}

int main() {

    Init();
    
    while (scanf("%d", &n) && n != -1)
        printf("%d\n", a[n]);

    return (0-0);

}

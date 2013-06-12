#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int T, N, K, Mod, sum, x, ans;

int p(int a, int b) {
    int ret = 1 % Mod, tmp = a % Mod;
    while (b) {
        if (b & 1) ret = ret * tmp % Mod;
        b /= 2;
        tmp = tmp * tmp % Mod;
    }
    return ret;
}

int main() {
    
    scanf("%d", &T);
    int c = 1;
    while (T--) {
        scanf("%d%d%d", &N, &K, &Mod);
        sum = 0;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &x);
            sum += (x % Mod);
            if (sum >= Mod) sum -= Mod;
        }
        ans = sum * (K % Mod) % Mod;
        ans = ans * p(N, K - 1) % Mod;
        printf("Case %d: %d\n", c++, ans);
    }
    
    return 0;

}

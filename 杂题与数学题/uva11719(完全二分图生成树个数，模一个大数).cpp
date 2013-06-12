#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long LL;

const LL Mod = 10000000000000007LL;

int T, r, c;
LL n, m;

LL mul(LL a, LL b) {
    LL ret = 0, tmp = a;
    while (b) {
        if (b & 1) ret = (ret + tmp) % Mod;
        b /= 2; 
        tmp = (tmp + tmp) % Mod;
    }
    return ret;
}

LL p(LL a, LL b) {
    LL ret = 1, tmp = a;
    while (b) {
        if (b & 1) ret = mul(ret, tmp);
        b /= 2;
        tmp = mul(tmp, tmp);
    }
    return ret;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &r, &c);
        n = (LL)r * (LL)c / 2;
        m = (LL)r * (LL)c - n;
        printf("%lld\n", mul(p(n, m - 1), p(m, n - 1)));
    }
    
    return 0;

}

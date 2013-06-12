#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long LLd;

LLd a, b, c, x_1, x_2, y_1, y_2;
LLd d, x, y, tx, ty;

LLd ExGcd(LLd a, LLd b) {
    if (b == 0) {x = 1; y = 0; return a;}
    LLd r = ExGcd(b, a%b);
    LLd t = x; x = y; y = t - a / b * y;
    return r;
}

bool Solve(LLd a, LLd b, LLd c) {
    d = ExGcd(a, b);
    if (c % d != 0) return false;
    x *= (c / d); y *= (c / d);
    tx = b / d; ty = -(a / d);
    return true;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    scanf("%I64d%I64d%I64d", &a, &b, &c);
    c = -c;
    scanf("%I64d%I64d%I64d%I64d", &x_1, &x_2, &y_1, &y_2);
    if (a == 0 || b == 0 || !Solve(a, b, c)) {
        if (a == 0 && b == 0) {
            if ( c == 0 ) printf("%I64d\n",(x_2 - x_1 + 1LL) * (y_2 - y_1 + 1LL));
                else printf("0\n");
        }
        if (a == 0 && b != 0) {
            if(c % b == 0 && c / b >= y_1 && c / b <= y_2)
                printf("%I64d\n", x_2 - x_1 + 1LL);
            else printf("0\n");
        }
        if (a != 0 && b == 0) {
            if(c % a == 0 && c / a >= x_1 && c / a <= x_2)
                printf("%I64d\n", y_2 - y_1 + 1LL);
            else printf("0\n");
        }
        if (a != 0 && b != 0) printf("0\n");
    }
    else {
        if (tx < 0) {
            x = -x; tx = -tx;
            x_1 = -x_1; x_2 = -x_2;
            swap(x_1, x_2);
        }
        if (ty < 0) {
            y = -y; ty = -ty;
            y_1 = -y_1; y_2 = -y_2;
            swap(y_1, y_2);
        }
        LLd kxmax, kxmin, kymax, kymin;
        kxmax = (x_2 - x >= 0 ? (x_2 - x) / tx : (x_2 - x) / tx - 1LL);
        kxmin = ((x_1 - x <= 0 || (x_1 - x) % tx == 0) ? 
                     (x_1 - x) / tx : (x_1 - x) / tx + 1LL);
        kymax = (y_2 - y >= 0 ? (y_2 - y) / ty : (y_2 - y) / ty - 1LL);
        kymin = ((y_1 - y <= 0 || (y_1 - y) % ty == 0) ? 
                     (y_1 - y) / ty : (y_1 - y) / ty + 1LL);
        if (min(kxmax, kymax) >= max(kxmin, kymin))
            printf("%I64d\n", min(kxmax, kymax) - max(kxmin, kymin) + 1LL);
                else printf("0\n");
    }

    return (0-0);

}

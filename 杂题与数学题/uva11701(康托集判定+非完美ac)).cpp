#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

bool f;
double x;
int t;

int main() {

    while (scanf("%lf", &x)) {
        f = true;
        for (int i = 1; i <= 20; ++i) {
            t = (int)(x * 3);
            if (t == 1) {f = false; break;}
            x = x * 3 - t;   
        }
        if (f) puts("MEMBER");
            else puts("NON-MEMBER");
    }

    return (0-0);

}

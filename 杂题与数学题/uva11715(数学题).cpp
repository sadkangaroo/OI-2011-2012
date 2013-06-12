#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

int o, cnt;
double a, b, c, tmp;

int main() {
    
    cnt = 0;
    while (scanf("%d", &o) && o) {
        scanf("%lf%lf%lf", &a, &b, &c);
        printf("Case %d: ", ++cnt);
        switch (o) {
            case 1 : printf("%.3lf %.3lf\n", (a + b) / 2 * c, (b - a) / c); break;
            case 2 : printf("%.3lf %.3lf\n", (b * b - a * a) / 2 / c, (b - a) / c); break; 
            case 3 : tmp = sqrt(2 * b * c + a * a);
                     printf("%.3lf %.3lf\n", tmp, (tmp - a) / b); break;
            case 4 : tmp = sqrt(a * a - 2 * b * c);
                     printf("%.3lf %.3lf\n", tmp, (a - tmp) / b); break;
        }
    }
    
    return 0;

}

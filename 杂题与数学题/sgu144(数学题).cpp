#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

double x, y, z;

int main() {

    scanf("%lf%lf%lf", &x, &y, &z);
    double a = (y - x) * 60.0;
    printf("%.7lf\n", fabs(1.0 - (a - z) * (a - z) / a / a));

    return (0-0);

}

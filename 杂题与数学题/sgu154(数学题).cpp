#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int Max_Ans = 5 * 100000000 + 5;

int Q, L, R, M;

bool check(int x) {
    int res = 0, t = 5;
    while (x >= t) {
        res += (x / t);
        t *= 5;
    }
    if (res >= Q) return true;
    return false;
}

bool OK(int x) {
    int res = 0, t = 5;
    while (x >= t) {
        res += (x / t);
        t *= 5;
    }
    if (res == Q) return true;
    return false;
}

int main() {

    scanf("%d", &Q);
    L = 0; R = Max_Ans;
    while (L + 1 < R) {
        M = (L + R) >> 1;
        if (check(M)) R = M;
            else L = M;
    }
    if(OK(R)) printf("%d\n", R);
      else printf("No solution\n");

    return (0-0);

}

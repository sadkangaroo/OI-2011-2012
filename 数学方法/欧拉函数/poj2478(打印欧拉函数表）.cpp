/*
  POJ 2478 Farey Sequence
  打印欧拉函数表 复杂度接近线性
  筛法过程中记录合数任意一个质因子
  素数n phi(n)=n-1
  合数n 如果n有一素因子p 
        (1) n/p与p互质，
            由积性函数性质得phi(n)=phi(n/p)*phi(p)=phi(n/p)*(p-1)
        (2) n/p与p不互质，则n/p%p==0
            由欧拉函数公式得phi(n)=phi(n/p)*p;
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long LLd;

const LLd Max_N = 1000006;

LLd N;
LLd phi[Max_N], fac[Max_N], s[Max_N];

void GetPhiTable() {
    memset(fac, -1, sizeof(fac));
    for (LLd i = 2; i < Max_N; ++i) {
        if (fac[i] == -1) {
            phi[i] = i - 1;
            for (LLd j = 2; j * i < Max_N; ++j)
                fac[j * i] = i;
        }
        else {
            if ((i / fac[i]) % fac[i]) 
                phi[i] = phi[i / fac[i]] * (fac[i] - 1);
            else phi[i] = phi[i / fac[i]] * fac[i];
        }
    }
    s[2] = phi[2];
    for (LLd i = 3; i < Max_N; ++i) 
        s[i] = s[i - 1] + phi[i];
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    
    GetPhiTable();
    while (scanf("%I64d", &N) && N)
        printf("%I64d\n", s[N]);
    
    return (0-0);

}

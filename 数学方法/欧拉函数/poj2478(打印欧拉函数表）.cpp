/*
  POJ 2478 Farey Sequence
  ��ӡŷ�������� ���ӶȽӽ�����
  ɸ�������м�¼��������һ��������
  ����n phi(n)=n-1
  ����n ���n��һ������p 
        (1) n/p��p���ʣ�
            �ɻ��Ժ������ʵ�phi(n)=phi(n/p)*phi(p)=phi(n/p)*(p-1)
        (2) n/p��p�����ʣ���n/p%p==0
            ��ŷ��������ʽ��phi(n)=phi(n/p)*p;
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

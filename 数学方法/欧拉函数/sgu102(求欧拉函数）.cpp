/*
  SGU 102 coprimes
  ��ʽ��ŷ�������������Ըģ�С�ڸĳɲ����ڣ�1��ʱ�����1�� 
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

int N;

int Euler(int n) {
    int res = n;
    for (int p = 2; p * p <= n; ++p)
        if (n % p == 0) {
            res = res / p * (p - 1);
            while (n % p == 0) n /= p;
        }
    if (n > 1) res = res / n * (n - 1);
    return res; 
}

int main() {

    scanf("%d", &N);
    printf("%d\n", Euler(N));

    return (0-0);

}

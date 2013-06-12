/*

����Ͱ����A����B����ÿ�ο��Դ�һ��Ͱ�ź�����һ��Ͱ��һ�����������һ��
Ͱ�У������ټ���ȫ�Ƶ�һ��Ͱ
���� ��log��2��((A+B)/gcd(A+B))	Ϊ���� ��Ϊ�𰸣������޽��
֤�� ���ȶ���һ����Ԫ��(p,q) ����(p/gcd(p,q),q/gcd(p,q))����ȫ�ȼ۵�
�ƻ��ʵ�һ����Ԫ��Ϊ������Ԫ�顣��ô������һ����������Ԫ��Ϊ(1,1)����ĳһ����������Ԫ��Ϊ(m,n) (m,n)=1.��ô����һ���Ķ�Ԫ�����Ϊ(m,2n+m)��(n,2m+n)
����m+n=2^k ��m,nΪ��������(m,2n)=1;(m,2n+m)=1;ͬ��(n,2m+n)=1���������Ƕ�����һ����������Ԫ�飬�Һ�Ϊ2^(k+1)������ѧ���ɷ����׵�֤��

*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

int a, b, t;

int gcd(int a,int b) {
    while (b) {t = a; a = b; b = t % b;}
    return a;
}

int main() {

    scanf("%d%d", &a, &b);
    if(a == 0 || b == 0) printf("0\n");
        else {
            int sum = (a + b) / gcd(a, b);
            int ans = (int)(log((double)(sum + 1))/log(2.0));
            if (1 << ans == sum) printf("%d\n", ans);
                else printf("-1\n");
        }
    
    return (0-0);

}

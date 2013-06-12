/*
ST�㷨������O(nlogn)��Ԥ����֮��ʵ��O(1)�Ĳ�ѯ������ֵ
Ԥ����� f[i][j]��ʾ[i,i+2^j-1]�ڵ���ֵ��
��ʼʱf[i][0]=h[i]������ʽΪ f[i][j]=max/min{f[i][j-1],f[i+(1<<(j-1))][j-1]},
�����������λ�����������ȡ���С����
ѯ��ʱ�� max/min(a,b)=max{f[a][k],f[b-(1<<k)+1][k]} 
����kΪ  log(b-a+1)/log(2); ������2^kС�����䳤��2^(k+1)�������䳤 
*/

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

long n,a,b;
long h[100005],f[100005][35]; 

void inimax(){
  long i,j;
  for(long i=1;i<=n;++i)
   f[i][0]=h[i];
  for(long j=1;j<=log((double)(n+1))/log(2.0);++j)
   for(long i=1;i+(1<<j)-1<=n;++i)
    f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}

long rmaxq(long a,long b){
  long k=(long)(log((double)(b-a+1))/log(2.0));
  return max(f[a][k],f[b-(1<<k)+1][k]);
}

int main(){
  return 0;
}

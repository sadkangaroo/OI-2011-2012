/*
��Ŀ���� ��һn*n�ø���ͼ��ÿ�ο����޸�һ���е�����Ҳ����ѯ��ĳ�����������֮��
�㷨��������״����Ķ�ά��ʽ 
*/

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

long n,order,x,y,a,l,b,r,t;
long c[1205][1205];

void modify(long x,long y,long delta){
 for(long i=x;i<=n;i+=(i&(-i)))
  for(long j=y;j<=n;j+=(j&(-j)))
    c[i][j]+=delta;
}

long sum(long x,long y){
 long ret=0;
 for(long i=x;i>0;i-=(i&(-i)))
  for(long j=y;j>0;j-=(j&(-j)))
   ret+=c[i][j];
 return ret;
}

int main(){
  scanf("0 %ld\n",&n);
  memset(c,0,sizeof(c));
  while(scanf("%ld",&order)&&order!=3){
    if(order==1){
      scanf("%ld%ld%ld",&x,&y,&a);
      modify(x+1,y+1,a);
    }          
    else{
      scanf("%ld%ld%ld%ld",&l,&b,&r,&t);
      printf("%ld\n",sum(r+1,t+1)-sum(l,t+1)-sum(r+1,b)+sum(l,b));
    }                        
  }
  return 0;
}

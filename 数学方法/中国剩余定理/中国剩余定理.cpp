/*
***�й�ʣ�ඨ��
��m1~mk������������������������������a1~ak,һ��ͬ�෽���� x=ai(mod mi)���н�
�ҽ��дΪx=x0(mod m) ����x0Ϊһ�ؽ⣬mΪ����mi�ĳ˻�
***��չ���й�ʣ�ඨ���������ͬ�෽����
��������ͬ�ڷ����� x=ai(mod mi) ��i����1~k����aiΪ������miΪ�������������
��һ�κϲ���c=a1(mod m1)��c=a2(mod m2)���н⣬��x0Ϊһ�ؽ⣬�����н�ɱ�ʾΪ
c=x0(mod lcm(m1,m2))(*),��˿����ã�*��ʽ�滻ǰǰ����ʽ�� ���ظ���k-1����ɵý�
��������ؽ�x0��  ����x0=x*m1+a1=y*m2+a2  �� x*m1-y*m2=a2-a2,
ע�⵽����m1��Ϊ��ʼʱ��lcm��m1,m2,...mk) 
��������չŷ����ýⲻ������ ���ж����޽⣬�н�����һ���ؽ⣬��Ӧ���ؽ�x0�� 
һ����ؽ�ת��Ϊ����ֵ��С������ֹ�������졣 
*/

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

bool flag;
long long n,m1,m2,r1,r2,c,d,x,y;

long long extend_gcd(long long a,long long b){
  if(b==0){x=1;y=0;return a;}
  long long r=extend_gcd(b,a%b);
  long long t=x;x=y;y=t-a/b*y;
  return r; 
} 

int main(){

  while(scanf("%I64d",&n)!=EOF){
    flag=true;
    scanf("%I64d%I64d",&m1,&r1);
    for(long long i=1;i<n;++i){
      scanf("%I64d%I64d",&m2,&r2);
       if(flag==false) continue;
      d=extend_gcd(m1,m2);
      c=r2-r1;
      if(c%d!=0){
        flag=false;
        continue;
      }
      long long t=m2/d;
      x=(c/d*x%t+t)%t;
      r1=m1*x+r1;
      m1=m1*m2/d;
    }
    if(flag) printf("%I64d\n",r1);
     else printf("-1\n");
  }

  return 0;

}

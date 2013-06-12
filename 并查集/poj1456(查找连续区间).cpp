/*
��Ŀ���⣺
����n����Ʒ��ÿ����Ʒ�м�ֵ��deadline,
������deadline֮ǰ������ÿһ����λʱ��ֻ����һ����Ʒ�����������������ֵ 

*̰�Ĳ��ԣ�
ÿ����Ʒ����Ҫ�����ǣ���ô��ȷ������˳��
�����򣬼�ֵ�Ӵ�С����ֵ��ͬ��ʱ������� 
1)�������Ա�������������������������Ʒ��������������ʱ��㣬
����֮�����Ʒռ�ã�������滻ʹ���ܼ�ֵ���ӣ���δ��ռ�ã������ռ��ʹ�ܼ�ֵ���ӣ�
���Ե�ǰ���ǵ���Ʒ�����Ա�����һ�������� 
2)�������������ұ������ˣ���Ȼ�ڵ�ǰ��������ʱ�������������������Ž��ӵĽ� 
3)���������Ա�����������Ȼ���ܱ����� 
�ɴ˵õ�n^2�㷨

*���ݽṹ�Ż�
����>���鼯 
�����ı�ռ��ʱ�����ͬһ�����ϣ����ڵ�Ϊ���������Ŀհ�ʱ��� 
�ڲ������������ʱ���ʱ��ֻ��ֱ�ӷ���deadline�������ĸ��ڵ�
��ռ��ʱ���ʱ��ֻ��Ҫ����ǰ��ռ�õĸ��ڵ�ĸ��ڵ���Ϊ�����ڵ��������ĸ��ڵ� 
*/


#include<iostream>

using namespace std;

struct pro{
  long p,d;
  bool operator >(const pro &t)const{
    if(p==t.p) return d>t.d;
    return p>t.p;
  }
}a[10003];

long n,ans,t;
long father[10003];


void qs(long l,long r){
  long i=l,j=r;
  pro tmp,mid=a[(l+r)/2];
  do{
    while(a[i]>mid) i++;
    while(mid>a[j]) j--;
    if(i<=j){
      tmp=a[i];a[i]=a[j];a[j]=tmp;
      i++;j--;
    }
  }while(i<=j);
  if(l<j) qs(l,j);
  if(i<r) qs(i,r);
}

long grand(long x){
  if(father[x]==x) return x;
  father[x]=grand(father[x]);
  return father[x];
}

int main(){
    
  while(scanf("%ld",&n)!=EOF){
    for(long i=1;i<=n;++i)
     scanf("%ld%ld",&(a[i].p),&(a[i].d));
    ans=0;
    qs(1,n);
    for(long i=0;i<=10001;++i)
      father[i]=i;
    for(long i=1;i<=n;++i){
      t=grand(a[i].d);
      if(t>0){
        father[t]=grand(t-1);
        ans+=a[i].p;
      }
    }
    printf("%ld\n",ans);
  }

  return 0;
 
}

/*
��״�������ά��һ���������޸�Ԫ��ֵ�����������ǰ׺�ͣ�����Ҳ�����ò��ֺ͵�֪ʶת��Ϊ�����
���޸���ѯ�ʵĸ��Ӷȶ���log�����
����һ����C��C[i]=A[i-i&(-i)+1]+��+A[i];���յ�ΪA[i]��һ�γ���Ϊ i&(-i) ������ 
��ÿ���޸�A����һ��Ԫ�ص�ֵʱ��ͬʱҪ�޸�c���飬����ǰ�޸��±�Ϊp�����´��޸ĵ��±�Ϊ p+p&(-p)
ÿ��ѯ��A����ǰp���ʱ��Ҫ����C����һЩ����ۼӣ�����ǰ�ۼӵ��±�Ϊp�����´��ۼӵ��±�Ϊ p-p&(-p)
*/
#include<iostream>
using namespace std;


long c[1005],c2[1005][1005],n;

//һά��ʽ 
void modify(long long p,long long del){
  for(;p<=n;p+=(p&(-p)))
    c[p]+=del;         //�޸�A[p]��ֵ 
}

long sum(long long p){
  long ret=0;
  for(;p>0;p-=(p&(-p)))        
    ret+=c[p];               //��A����ǰp��� 
  return ret;
}

//��ά��ʽ����>�������ƹ�����ά��ʽ 
void modify_2(long x,long y,long delta){
 for(long i=x;i<=n;i+=(i&(-i)))
  for(long j=y;j<=n;j+=(j&(-j)))                 
    c2[i][j]+=delta;                  //�޸�A[p]��ֵ 
}

long sum_2(long x,long y){
 long ret=0;
 for(long i=x;i>0;i-=(i&(-i)))
  for(long j=y;j>0;j-=(j&(-j)))
   ret+=c2[i][j];                   //��A����ǰp��� 
 return ret;
}

int main(){
  return 0;
}

/*
�ɶ���ʣ���������ۿ�֪��pΪ�������ı�Ҫ����Ϊ 
x^2=1(mod p)���ҽ�������x=+/- 1��mod p)
���ɷ���С����ã���(p,a)=1,��pΪ�����ı�Ҫ����Ϊ 
a^(p-1)=1(mod p) 
���������������Ƴ������������Բ���
���� n < 2,152,302,898,747, ֻҪ��2,3,5,7,11Ϊ�ײ��Լ��� 
�ж�һ����p�Ƿ�Ϊ����������
int pri[]={2,3,5,7,11};
bool check(int p){ 
  if(p<2) return false;
  if(p==2||p==3||p==5||p==7||p==11) return true;
  if(p%2==0||p%3==0||p%5==0||p%7==0||p%11==0) return false;
  bool ans=true;
  for(int i=0;i<5;++i)
    ans&=Miller_Rabin(pri[i],p);
  return ans; 
} 
��� 
bool Miller_Rabin(int a,int p){
  int d=p-1;
  while(!(d&1)) d>>=1;
  long long t=get_power(a,d,p);
  while(d!=p-1){
    if(t==p-1) return true;  //��Ϊ-1,֮ǰһ�������߰��������֮����1�� ֹͣ�жϷ���true 
    if(t==1){                //��Ϊ1��֮ǰһ��û����-1�������ǵ�һ�η���true�����򷵻�false  
      if(d&1) return true;
      return false;
    }
    t=(t*t)%p;
    d<<=1;
  }
  return false;               //֮ǰ���ٽ��й�һ�Σ���֮ǰ��û�г���1��-1�� 
}                             //�����һ�β��ܷ������Ϸ���С����p��������Ϊ����������false  
 
*/ 
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

int main(){
  return 0;
}

#include<iostream>
#include<string>
#include<math.h>
using namespace std;

/*

 ���鼯������ϵĺϲ����ѯ����
*����ؼ�����ʱ�临�Ӷȶ���O(1)�� 
*��ʼʱÿ��Ԫ�ظ�Ϊһ������,rank����Ϊ1����ÿ�����ϸ߶�Ϊ1��

*/
 
 long father[10003],rank[10003];
 
 //(1)��ѯԪ��x��������
 long grand(long x){
   if(father[x]==x) return x;
   father[x]=grand(father[x]);//��Ҫ�Ż���·��ѹ��
   return father[x]; 
 }
 //(2)�ϲ���������
 void uni(long x,long y){
   long fx=grand(x),fy=grand(y);
   if(fx==fy) return;
   if(rank[fx]>rank[fy]) father[fy]=fx;//�Ƚ���Ҫ���Ż���rank�ϲ� 
    else{
      father[fx]=fy;
      if(rank[fx]==rank[fy]) rank[fy]++;
    }
 } 

int main(){
  return 0;
}

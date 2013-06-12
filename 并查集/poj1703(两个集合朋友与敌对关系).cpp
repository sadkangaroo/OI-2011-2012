/*
  ��Ŀ���⣺n��Ԫ�أ���������������ͬ�ļ��ϣ�ÿ�θ�����������Ԫ�����ڲ�ͬ���ϻ���ѯ������Ԫ��֮��Ĺ�ϵ
  �㷨����չ�Ĳ��鼯(����������ϵжԹ�ϵ�����Բ��鼯�����op[i]��ʾi��һ������,��op[i]==-1��ʾδ֪��ÿ�ζ���һ���ϵ��a��b�ǵ���
  ��ôa��b�ĵ�������ͬһ���ϣ�b��a�ĵ�������ͬһ���ϣ���op[a]==-1��op[a]=b,��op[b]==-1��op[b]=a; 
  ѯ��ʱ��a��b������<=>a��b����ͬһ������ 
          a��b�ǵ���<=>a��b�ĵ�������ͬһ����
          not for sure<=>����
*/
#include<iostream>
using namespace std;

char ch;
long t,n,m,a,b;
long fa[100005],rank[100005],op[100005];

long grand(long x){
  if(x==-1) return -100;
  if(fa[x]==x) return x;
  fa[x]=grand(fa[x]);
  return fa[x];
}

void uni(long x,long y){
  long fx=grand(x),fy=grand(y);
  if(fx==fy) return;
  if(rank[fx]<rank[fy]) fa[fx]=fy;
   else{
     fa[fy]=fx;
     if(rank[fx]==rank[fy]) rank[fx]++;
   }
}

int main(){
 scanf("%ld\n",&t);
 while(t--){
   scanf("%ld %ld\n",&n,&m);
   for(long i=1;i<=n;++i){
    fa[i]=i;
    rank[i]=1;
    op[i]=-1;
   }
   for(long i=1;i<=m;++i){
     scanf("%c %ld %ld\n",&ch,&a,&b);
     if(ch=='D'){
      if(op[a]==-1) op[a]=b;
        else uni(op[a],b);
      if(op[b]==-1) op[b]=a;
        else uni(op[b],a);
     }
     else{
       if(grand(a)==grand(b)) printf("In the same gang.\n");
        else if(grand(a)==grand(op[b])) printf("In different gangs.\n");
         else printf("Not sure yet.\n");
     }
   }
 }   
    
 return 0;
}

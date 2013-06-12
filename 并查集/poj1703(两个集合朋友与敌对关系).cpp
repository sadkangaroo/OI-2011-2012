/*
  题目大意：n个元素，它们属于两个不同的集合，每次告诉你哪两个元素属于不同集合或者询问两个元素之间的关系
  算法：拓展的并查集(解决两个集合敌对关系），对并查集添加域op[i]表示i的一个敌人,若op[i]==-1表示未知，每次读入一组关系：a与b是敌人
  那么a与b的敌人属于同一集合，b与a的敌人属于同一集合，若op[a]==-1则op[a]=b,若op[b]==-1则op[b]=a; 
  询问时，a与b是朋友<=>a与b属于同一个集合 
          a与b是敌人<=>a与b的敌人属于同一集合
          not for sure<=>其他
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

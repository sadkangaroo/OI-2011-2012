/*
  基于树的贪心
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int Max_E=200020;
const int Max_V=100010;

struct node{
  int to;
  node *lnk;
  node(){}
  node(int _to,node *_lnk):to(_to){lnk=_lnk;}
}Tnull,*null=&Tnull,*T[Max_V],buf[Max_E];
int cbuf=-1;

inline void make_edge(int x,int y){
  cbuf++;buf[cbuf]=node(y,T[x]);T[x]=buf+cbuf;  
}

int h[Max_V],cut[Max_V],stretch[Max_V];
int v,s,ai,bi,l,r,chk,st;

int search(int fa,int cur){ 
  cut[cur]=0;int tmp=0;
  for(node *t=T[cur];t!=null;t=t->lnk)
      if(t->to!=fa)
         cut[cur]+=search(cur,t->to);
  for(node *t=T[cur];t!=null;t=t->lnk)
      if(t->to!=fa)
         h[tmp++]=stretch[t->to];
  sort(h,h+tmp,greater<int>());
  h[tmp]=-1;
  st=0;
  while(st<tmp&&h[st]+h[st+1]+2>chk){                                                                
        cut[cur]++;
        st++;
  }
  stretch[cur]=h[st]+1;
  return cut[cur]; 
}

int main(){

  freopen("exercise.in","r",stdin);
  freopen("exercise.out","w",stdout);

  scanf("%d%d",&v,&s);
  for(int i=1;i<=v;++i) 
      T[i]=null;
  for(int i=1;i<v;++i){
      scanf("%d%d",&ai,&bi);
      make_edge(ai,bi);make_edge(bi,ai);
  }
  
  l=0;r=Max_V; 
  while(l+1!=r){                
        chk=(l+r)/2;
        if(search(-1,1)<=s)
           r=chk;
             else l=chk;
  } 

  printf("%d\n",r);
  
  return 0;

}

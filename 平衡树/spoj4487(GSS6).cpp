/*
  2011/1/16
  splay模板题（包括求给定区间内最大连续子段）
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int NEG=-100000000;
const int Max_BUF=250000;

struct node{ 
  int key,size,ms,mls,mrs,sum;
  node *c[2]; 
  node():ms(NEG),mls(NEG),mrs(NEG),sum(0),size(0){c[0]=c[1]=this;} 
  node(int _key,node* _c0,node* _c1):key(_key){c[0]=_c0;c[1]=_c1;} 
  node* rz(){
    size=c[0]->size+c[1]->size+1;
    sum=c[0]->sum+c[1]->sum+key;
    mls=max(max(c[0]->mls,c[0]->sum+key),c[0]->sum+key+c[1]->mls);
    mrs=max(max(c[1]->mrs,c[1]->sum+key),c[1]->sum+key+c[0]->mrs);
    ms=max(max(c[0]->ms,c[1]->ms),key);
    ms=max(max(ms,c[0]->mrs+key+c[1]->mls),max(c[0]->mrs+key,c[1]->mls+key));
    return this;
  }
}Tnull,*null=&Tnull,buf[Max_BUF];
int cbuf=-1;

struct splay{ 
   
  node *root; 
   
  splay(){ 
    cbuf++;
    root=( *(buf + cbuf) = node(*null) ).rz();
    root->key=0; 
  }
   
  void zig(bool d){ 
    node *t=root->c[d]; 
    root->c[d]=null->c[d]; 
    null->c[d]=root; 
    root=t; 
  } 
   
  void zigzig(bool d){ 
    node *t=root->c[d]->c[d]; 
    root->c[d]->c[d]=null->c[d]; 
    null->c[d]=root->c[d]; 
    root->c[d]=null->c[d]->c[!d]; 
    null->c[d]->c[!d]=root->rz(); 
    root=t; 
  } 
  
  void finish(bool d){ 
    node *t=null->c[d],*p=root->c[!d]; 
    while(t!=null){ 
      t=null->c[d]->c[d]; 
      null->c[d]->c[d]=p; 
      p=null->c[d]->rz(); 
      null->c[d]=t;  
    } 
    root->c[!d]=p; 
  } 
   
  void select(int k){ 
    int t; 
    for(;;){ 
      bool d=k>(t=root->c[0]->size); 
      if(k==t) break; 
      if(d) k-=(t+1); 
      bool dd=k>(t=root->c[d]->c[0]->size); 
      if(k==t){zig(d);break;} 
      if(dd) k-=(t+1); 
      d!=dd?zig(d),zig(dd):zigzig(d); 
    }
    finish(0),finish(1); 
    root->rz(); 
  } 
  
  void ins(int x){  
    //search(x); 
    node *oldroot=root; 
    cbuf++;
    root=&( *(buf + cbuf)=node(x,oldroot->c[0],oldroot) );
    oldroot->c[0]=null; 
    oldroot->rz(); 
    root->rz();
  } 
   
  void del(){ 
    //search(x); 
    node *oldroot=root; 
    root=root->c[1]; 
    select(0); 
    root->c[0]=oldroot->c[0]; 
    root->rz(); 
  }
   
}sp; 

int N,Q;

int main(){
     
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%d\n",&N);
  int tmp;
  for(int i=1;i<=N;++i){
    sp.select(i-1);
    scanf("%d",&tmp);
    sp.ins(tmp);
  }
  scanf("%d\n",&Q);
  char c;
  int pos,x,y;
  for(int i=1;i<=Q;++i){
    c=getchar();
    if(c=='I'){
      scanf("%d%d\n",&pos,&x);
      sp.select(pos-1);
      sp.ins(x);
    }
    if(c=='D'){
      scanf("%d\n",&pos);
      sp.select(pos-1);
      sp.del();
    }
    if(c=='R'){
      scanf("%d%d\n",&pos,&x);
      sp.select(pos-1);
      sp.root->key=x;
    }
    if(c=='Q'){
      scanf("%d%d\n",&x,&y);
      if(x==1){
        sp.select(y);
        printf("%d\n",sp.root->c[0]->ms);
      }
      else{
        sp.select(x-2);
        node *oldroot=sp.root; 
        sp.root=sp.root->c[1];
        sp.select(y-x+1);
        printf("%d\n",sp.root->c[0]->ms);
        oldroot->c[1]=sp.root;
        sp.root=oldroot;
      }
    }
  }
    
  return 0;

}

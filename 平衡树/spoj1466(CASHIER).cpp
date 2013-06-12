#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<iterator>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<list>
#include<utility>
#include<complex>

using namespace std;

const int oo=0x7fffffff;
const int Max_Buf=100005;

struct node{
  int key,size;
  node* c[2];
  node():key(oo),size(0){ c[0]=c[1]=this; }
  node(int _key,node *_c0,node *_c1):key(_key){ c[0]=_c0;c[1]=_c1; }
  node* rz(){ return size=c[0]->size+c[1]->size+1,this; }
}Tnull,*null=&Tnull,buf[Max_Buf];
int cbuf;

struct splay{
  
  node* root;
  
  void reset(){
    cbuf=-1;
    cbuf++;root=(buf[cbuf]=node(*null)).rz();  
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
    bool d,dd;int t;
    for(;;){
      d=(k>(t=root->c[0]->size));
      if(k==root->c[0]->size) break;
      if(d) k-=(t+1);
      dd=(k>(t=root->c[d]->c[0]->size));
      if(k==root->c[d]->c[0]->size) { zig(d);break; }
      if(dd) k-=(t+1);
      d!=dd?zig(d),zig(dd):zigzig(d);
    }
    finish(0);finish(1);
    root->rz();
  }
  
  void search(int x){
    bool d,dd;
    for(;;){
      d=(x>root->key);
      if(root->c[d]==null) break;
      dd=(x>root->c[d]->key);
      if(root->c[d]->c[dd]==null) { zig(d);break; }
      d!=dd?zig(d),zig(dd):zigzig(d);
    }
    finish(0);finish(1);
    root->rz();
    if(x>root->key) select(root->c[0]->size+1);
  }
  
  void ins(int x){
    search(x);
    node *oldroot=root;
    cbuf++;
    root=&(buf[cbuf]=node(x,oldroot->c[0],oldroot));
    oldroot->c[0]=null;
    oldroot->rz();
    root->rz();
  }
   
}sp;

int T,M,lim,delta,sum,lef;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d",&T);
  char c;int k;
  while(T--){
    sp.reset();
    delta=lef=0;
    scanf("%d%d\n",&M,&lim);
    while(M--){
      scanf("%c %d\n",&c,&k);
      if(c=='I'){
        if(k<lim) continue;
        sp.ins(k-delta);
      }
      if(c=='A') delta+=k;
      if(c=='S'){
        delta-=k;
        sp.search(lim-delta);
        lef+=sp.root->c[0]->size;
        sp.root->c[0]=null;
        sp.root->rz();
      }
      if(c=='F'){
        sum=sp.root->size-1;
        if(k>sum) printf("-1\n");
        else{
          sp.select(sum-k);
          printf("%d\n",sp.root->key+delta);
        }
      }
    }
    printf("%d\n",lef);
  }

  return 0;

}

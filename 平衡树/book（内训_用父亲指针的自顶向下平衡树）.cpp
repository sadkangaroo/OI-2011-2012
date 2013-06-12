/*
  一棵不按关键字排序的splay，但需要通过域值访问到splay中的结点，
  所用通过哈希取地址，自底向上记路径，自顶向下splay 
  不得不用父亲指针 
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int oo=0x7fffffff;
const int Max_N=200000;

char cmd,tmp;
int a[Max_N];
int n,m,s,k,delta;

struct node{
  int lab,size;
  bool f;
  node *c[2],*fa;
  node():lab(0),size(0){c[0]=c[1]=fa=this;f=false;}
  node(int _lab,node* _c0,node* _c1):lab(_lab){c[0]=_c0;c[1]=_c1;f=false;}
  node* rz();
}Tnull,*null=&Tnull,buf[Max_N],*locate[Max_N];
int cbuf=0;

node* node::rz(){
  c[0]->fa=c[1]->fa=this;                 //和normal比，只要在更新size的时候更新父亲指针 
  fa=null;
  return size=c[0]->size+c[1]->size+1,this;
}

struct splay{
  
  node* root;
  
  splay(){   
    root=( *(buf + cbuf++) = node(*null) ).rz();
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
      if(k==t) {zig(d);break;}
      if(dd) k-=(t+1);
      d!=dd?zig(d),zig(dd):zigzig(d);      
    }
    finish(0);finish(1);
    root->rz();
  }
  
  void search(node* p){
    while(p!=root){
      p->f=true;               //和normal比需要自底向上记录路劲 
      p=p->fa;
    }
    for(;;){ 
      bool d=root->c[1]->f; 
      if(root->c[d]->f==false)break; 
      bool dd=root->c[d]->c[1]->f;  
      if(root->c[d]->c[dd]->f==false){root->c[d]->f=false;zig(d);break;}   //再改进方式自顶向下splay 
      root->c[d]->f=root->c[d]->c[dd]->f=false;
      d!=dd?zig(d),zig(dd):zigzig(d); 
    } 
    finish(0),finish(1); 
    root->rz(); 
  }
  
  void ins(int x){
    node *oldroot=root;
    root=&( *(buf + cbuf++)=node(x,oldroot->c[0],oldroot) );
    locate[x]=root;                //和normal相比需要实时修改locate（hash) 
    oldroot->c[0]=null;
    oldroot->rz();  
    root->rz();
  }                  
  
  void del(int x){
    search(locate[x]);
    node *oldroot=root;
    root=root->c[1];
    select(0);
    root->c[0]=oldroot->c[0];
    root->rz();
  }                   
  
} sp;

int main(){

  freopen("book.in","r",stdin);
  freopen("book.out","w",stdout);
  
  scanf("%d %d\n",&n,&m);
  for(int i=1;i<=n;++i){
    scanf("%d",a+i);
    sp.select(i-1);sp.ins(a[i]);
  }
    
  for(int i=1;i<=m;++i){
    while((cmd=getchar())&&(cmd=='\n'||cmd==' ')){}
    while((tmp=getchar())&&tmp!=' '){}
    switch(cmd){
      case'T':
        scanf("%d",&s);
        sp.del(s);sp.select(0);sp.ins(s);
        break;
      case'B':
        scanf("%d",&s);
        sp.del(s);sp.select(n-1);sp.ins(s);
        break;
      case'I':
        scanf("%d%d",&s,&delta);
        sp.search(locate[s]);
        delta+=sp.root->c[0]->size;
        sp.del(s);
        sp.select(delta);
        sp.ins(s);
        break;
      case'A':
        scanf("%d",&s);
        sp.search(locate[s]);
        printf("%d\n",sp.root->c[0]->size);
        break;
      case'Q':
        scanf("%d",&k);
        sp.select(k-1);
        printf("%d\n",sp.root->lab);              
        break;      
    }
  }

  return 0;

}

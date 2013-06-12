/*
  Æ½ºâÊ÷Ó¦ÓÃ
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int oo=0x7fffffff;
const int Max_C=1000010;
const int Max_N=10010;

char ch;
int hash[Max_C],col[Max_N],lef[Max_N];
int n,m,p,c,ll,rr,sum;

struct node{ 
  int key,size;
  node *c[2];
  node():key(0),size(0){c[0]=c[1]=this;} 
  node(int key_,node* c0_,node* c1_):key(key_){c[0]=c0_;c[1]=c1_;} 
  node* rz(){return size=c[0]->size+c[1]->size+1,this;} 
}Tnull,*null=&Tnull,buf[Max_N*50];
int cbuf=0;

struct splay{ 
   
  node *root; 
   
  splay(){ 
    root=( *(buf + cbuf++) = node(*null) ).rz();
    root->key=oo;
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
      if(k==t||root->c[d]==null)break; 
      if(d)k-=t+1; 
      bool dd=k>(t=root->c[d]->c[0]->size); 
      if(k==t||root->c[d]->c[dd]==null){zig(d);break;} 
      if(dd)k-=t+1; 
      d!=dd?zig(d),zig(dd):zigzig(d); 
    } 
    finish(0),finish(1); 
    root->rz(); 
  } 
   
  void search(int x){ 
    for(;;){ 
      bool d=x>root->key; 
      if(root->c[d]==null)break; 
      bool dd=x>root->c[d]->key; 
      if(root->c[d]->c[dd]==null){zig(d);break;} 
      d!=dd?zig(d),zig(dd):zigzig(d); 
    } 
    finish(0),finish(1); 
    root->rz(); 
    while(x>root->key)select(root->c[0]->size+1); 
    while(root->c[0]!=null&&root->c[0]->key==root->key) select(root->c[0]->size-1);
  } 
  
  void ins(int x){ 
    search(x); 
    node *oldroot=root; 
    root=&( *(buf + cbuf++)=node(x,oldroot->c[0],oldroot) );
    oldroot->c[0]=null; 
    oldroot->rz(); 
    root->rz();
  } 
   
  void del(int x){ 
    search(x); 
    node *oldroot=root; 
    root=root->c[1]; 
    select(0); 
    root->c[0]=oldroot->c[0]; 
    root->rz(); 
  }
   
};

struct seg_node{
  int l,r;
  splay sp;
};

struct seg_tree{
       
  seg_node T[Max_N*4];
  
  void build(int cur,int l,int r){      
    T[cur].l=l;T[cur].r=r;
    for(int i=l;i<=r;++i)
      T[cur].sp.ins(lef[i]);
    if(l==r) return;
    build(cur*2,l,(l+r)/2);build(cur*2+1,(l+r)/2+1,r);
  }

  void modify(int cur,int pos,int a,int b){
    T[cur].sp.del(a);
    T[cur].sp.ins(b);
    if(T[cur].l==T[cur].r) return;
    if(pos<=(T[cur].l+T[cur].r)/2)
      modify(cur*2,pos,a,b);
    else modify(cur*2+1,pos,a,b);
  }

  void query(int cur,int l,int r){
    if(T[cur].l==l&&T[cur].r==r){
      T[cur].sp.search(ll);
      sum+=T[cur].sp.root->c[0]->size;
      return;
    } 
    int mid=(T[cur].l+T[cur].r)/2;
    if(r<=mid){query(cur*2,l,r);return;}
    if(l>=mid+1){query(cur*2+1,l,r);return;}
    query(cur*2,l,mid);
    query(cur*2+1,mid+1,r);
  }
  
}st;

int main(){
  
  freopen("color.in","r",stdin);
  freopen("color.out","w",stdout);
  
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;++i)
    scanf("%d",col+i);
  
  memset(hash,0,sizeof(hash));
  for(int i=1;i<=n;++i){
    lef[i]=hash[col[i]];
    hash[col[i]]=i;
  }  
  st.build(1,1,n);
  
  for(int i=1;i<=m;++i){        
    while((ch=getchar())&&ch!='Q'&&ch!='R'){}
    if(ch=='R'){
      scanf("%d%d",&p,&c);
      for(int j=p+1;j<=n;++j)
        if(col[j]==col[p]){
          st.modify(1,j,lef[j],lef[p]);
          lef[j]=lef[p];
          break;
        }
      st.modify(1,p,lef[p],0);
      lef[p]=0;
      for(int j=p-1;j>=1;--j)
        if(col[j]==c){
          st.modify(1,p,lef[p],j);
          lef[p]=j;
          break;
        }
      for(int j=p+1;j<=n;++j)
        if(col[j]==c){
          st.modify(1,j,lef[j],p);
          lef[j]=p;
          break;
        }
      col[p]=c;
    }
    else{
      scanf("%d%d",&ll,&rr);
      sum=0;      
      st.query(1,ll,rr);
      printf("%d\n",sum);
    }
  }
  
  return 0;

}

/*
  动态规划的坐标优化
  将前驱状态表示为坐标轴内的点，通过对点进行缩放旋转（可以转化为对坐标轴）
  从而使得前驱状态的约束条件降一维，从而可以用线段树之类的数据结构
  维护最优前驱。 
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int Max_M=400010;
const int Max_N=100010;

int f[Max_N],h[Max_N];
int w,n,tx,ty,tv,ans;

struct P_node{
  int x,y,v;
  P_node(){}
  P_node(int _x,int _y,int _v):x(_x),y(_y),v(_v){}
  bool operator < (const P_node &t)const{
    if(x==t.x) return y>t.y;
     return  x<t.x;
  }
}nodes[Max_N];

struct T_node{
  int l,r,s;
  T_node *lch,*rch;
  T_node(){}
  T_node(int _l,int _r,int _s);
}T_null,*null=&T_null,buf[Max_M];
int cbuf;
T_node::T_node(int _l,int _r,int _s):l(_l),r(_r),s(_s){lch=rch=null;}

void build(T_node *c,int a,int b){
  *c=T_node(a,b,0);
  if(a==b) return;
  int mid=(a+b)/2;
  c->lch=buf+(++cbuf);build(c->lch,a,mid);  
  c->rch=buf+(++cbuf);build(c->rch,mid+1,b);
}

int search(T_node *c,int a,int b){
  if(h[c->l]==a&&h[c->r]==b) return c->s;
  int mid=(c->l+c->r)/2;
  if(b<=h[mid]) return search(c->lch,a,b);
  if(a>=h[mid+1]) return search(c->rch,a,b);
  return search(c->lch,a,h[mid])>?search(c->rch,h[mid+1],b);
}

void insert(T_node *c,int ty,int ts){
  (c->s)>?=ts;
  if(c->l==c->r) return;
  int mid=(c->l+c->r)/2;
  if(ty<=h[mid]) insert(c->lch,ty,ts);
  if(ty>=h[mid+1]) insert(c->rch,ty,ts);
}

int main(){

  freopen("free.in","r",stdin);
  freopen("free.out","w",stdout);

  scanf("%d%d",&w,&n);
  for(int i=1;i<=n;++i){
    scanf("%d%d%d",&tx,&ty,&tv);
    nodes[i]=P_node(tx*2+ty,-tx*2+ty,tv);
    h[i]=-tx*2+ty;
  }
  sort(nodes+1,nodes+n+1);
  sort(h+1,h+n+1);
  for(int i=1;i<=n;++i)
    f[i]=nodes[i].v;
  
  cbuf=-1;
  T_node *root=buf+(++cbuf);
  build(root,1,n);
  for(int i=1;i<=n;++i){
    f[i]=search(root,nodes[i].y,h[n])+nodes[i].v;
    insert(root,nodes[i].y,f[i]);
  }
  
  ans=0;
  for(int i=1;i<=n;++i)
    ans>?=f[i];
  printf("%d\n",ans);
  
  return 0;

}

/*
  将二分图上的最大割转化为最小割 
*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

#define FF for(int i=1;i<=n;++i) for(int j=1;j<=m;++j)

const int oo=0x7fffffff;
const int Max_E=550000;
const int Max_N=105;

struct Lnk_Node{
  int tox,toy,cap;
  Lnk_Node  *lnk,*pair;
  Lnk_Node(){}
  Lnk_Node(int _tox,int _toy,int _cap,Lnk_Node *_lnk,Lnk_Node *_pair):tox(_tox),toy(_toy),cap(_cap){
    lnk=_lnk;
    pair=_pair;
  }
}Gnull,*null=&Gnull,buf[Max_E],*g[Max_N][Max_N];
int cbuf=-1;

bool found;
int a[Max_N][Max_N],b[Max_N][Max_N],c[Max_N][Max_N];
int dx[5]={0,0,0,1,-1},dy[5]={0,1,-1,0,0};
int d[Max_N][Max_N],v[Max_N*Max_N],flow,aug;
int n,m,sx,sy,tx,ty,tot,di,dj,sum;

inline int check(int cx,int cy){
  if(cx<1||cx>n||cy<1||cy>m) return 0;
  int ret=4;
  if(cx==1) ret--;if(cx==n) ret--;
  if(cy==1) ret--;if(cy==m) ret--;
  return ret;
} 

inline void make_edge(int xa,int ya,int xb,int yb,int va,int vb){
  cbuf++;buf[cbuf]=Lnk_Node(xb,yb,va,g[xa][ya],buf+cbuf+1);g[xa][ya]=buf+cbuf;
  cbuf++;buf[cbuf]=Lnk_Node(xa,ya,vb,g[xb][yb],buf+cbuf-1);g[xb][yb]=buf+cbuf;
}

void augment(int nx,int ny){
  int tmp=aug,min_d=tot-1;
  Lnk_Node *t;
  if(d[sx][sy]>=tot) return;
  if(nx==tx&&ny==ty){
    found=true;     
    flow+=aug;
    return;
  }
  for(t=g[nx][ny];t!=null;t=t->lnk)
    if(t->cap>0){
      if(d[nx][ny]==d[t->tox][t->toy]+1){  
        if(t->cap<aug) aug=t->cap;  
        augment(t->tox,t->toy);                       
        if(d[sx][sy]>=tot) return;
        if(found) break;
        aug=tmp;
      }
      if(d[t->tox][t->toy]<min_d) min_d=d[t->tox][t->toy]; 
    }
  if(found){
    t->cap-=aug;
    t->pair->cap+=aug;
  }
  else{
    if(--v[d[nx][ny]]==0) d[sx][sy]=n;
    d[nx][ny]=min_d+1;
    v[d[nx][ny]]++;
  }
}

int main(){

  freopen("land.in","r",stdin);
  freopen("land.out","w",stdout);

  scanf("%d%d",&n,&m);
  FF scanf("%d",&a[i][j]);
  FF scanf("%d",&b[i][j]);
  FF scanf("%d",&c[i][j]);
  FF g[i][j]=null;
  g[sx][sy]=g[tx][ty]=null;  
  sx=sy=0;tx=n+1;ty=m+1;
  sum=0;
  FF{
    if((i+j)&1){
      make_edge(sx,sy,i,j,a[i][j],0);
      make_edge(i,j,tx,ty,b[i][j],0);
    }
    else{
      make_edge(sx,sy,i,j,b[i][j],0);
      make_edge(i,j,tx,ty,a[i][j],0);
    }
    for(int u=1;u<=4;++u){
      di=i+dx[u];dj=j+dy[u];
      if(check(di,dj))
        make_edge(i,j,di,dj,c[i][j]+c[di][dj],0);
    }
    sum+=(a[i][j]+b[i][j]+check(i,j)*c[i][j]);
  }

  tot=n*m+2;
  memset(d,0,sizeof(d));
  memset(v,0,sizeof(v));
  v[0]=tot;
  flow=0;
  
  while(d[sx][sy]<tot){
    aug=oo;
    found=false;
    augment(sx,sy);
  }

  printf("%d\n",sum-flow);

  return 0;

}

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>

using namespace std;

const int oo=10005,Max_N=100005;
const double eps=1e-7;

double L;
int T,N,xi,yi,top1,top2;

inline int dbc(double a,double b){return fabs(a-b)<eps?0:(a>b?1:-1);}

struct node{
  int lab;double x,y;
  node(int _lab=-1,double _x=0,double _y=0):lab(_lab),x(_x),y(_y){}
  node operator - (node &t){return node(-1,x-t.x,y-t.y);}
  bool operator == (const node &t)const{
    return (dbc(x,t.x)==0&&dbc(y,t.y)==0);
  }
  bool operator < (const node &t)const{
    if((*this)==t) return (lab<t.lab); 
    return (dbc(y,t.y)==-1||dbc(y,t.y)==0&&dbc(x,t.x)==-1);
  }
}pt[Max_N],stk[Max_N];

inline int cross(node a,node b){return dbc(a.x*b.y-a.y*b.x,0);}

inline double dis(node t){return sqrt(t.x*t.x+t.y*t.y);}

void unique_sort(){
  sort(pt+1,pt+N+1);
  int p=1;
  for(int i=2;i<=N;++i) if(!(pt[i]==pt[i-1])){pt[++p]=pt[i];} 
  N=p;
}

void Graham_Scan(){
  top1=0;
  for(int i=1;i<=N;++i){
    while(top1>=2&&cross(stk[top1]-stk[top1-1],pt[i]-stk[top1-1])<=0) 
      top1--;
    stk[++top1]=pt[i];
  }
  top2=top1;top1--;
  for(int i=N-1;i>=1;--i){
    while(top2-top1>=2&&cross(stk[top2]-stk[top2-1],pt[i]-stk[top2-1])<=0) 
      top2--;
    stk[++top2]=pt[i];
  }
}

int main(){

  scanf("%d",&T);
  while(T--){
    scanf("%d",&N);
    for(int i=1;i<=N;++i){
      scanf("%d%d",&xi,&yi);
      pt[i]=node(i,(double)xi,(double)yi);
    }
    if(N==1) {printf("0.00\n1\n");if(T) printf("\n");continue;}
    unique_sort();
    Graham_Scan();
    L=0;
    for(int i=2;i<=top2;++i) L+=dis(stk[i]-stk[i-1]);
      printf("%.2lf\n",L);
    for(int i=1;i<top2-1;++i) printf("%d ",stk[i].lab);
      printf("%d\n",stk[top2-1].lab);
    if(T) printf("\n");
  }
    
  return (0-0);
    
}

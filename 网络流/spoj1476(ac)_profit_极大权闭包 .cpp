#include<iostream>

using namespace std;

const long Max_N=55503;
const long INF=0x7fffffff;

struct edge{
  long lab,cap,pair,next;
}e[320003];

long tt,n,m,s,t,tot,x,ai,bi,ci,sum,point;

long flow,aug;
long c[Max_N],cur[Max_N],v[Max_N],d[Max_N],min_d[Max_N];
bool found;

void add(long a,long b,long x,long y){
  point++;e[point].lab=b;e[point].cap=x;e[point].next=c[a];e[point].pair=point+1;c[a]=point;
  point++;e[point].lab=a;e[point].cap=y;e[point].next=c[b];e[point].pair=point-1;c[b]=point;
}

void augment(long now){
  if(d[s]>=tot) return;
  long i,tmp=aug;
  if(now==t){
   found=true;
   flow+=aug;
   return;
  }
  i=cur[now];
  while(i){
   if(e[i].cap){
     if(d[now]==d[e[i].lab]+1){
       cur[now]=i;
       if(e[i].cap<aug) aug=e[i].cap;
       augment(e[i].lab);
       if(found) break;
       if(d[s]>=tot) return;
       aug=tmp;
     }
     if(d[e[i].lab]<min_d[now]) min_d[now]=d[e[i].lab];
   } 
   i=e[i].next;
  }
   if(found){
     e[i].cap-=aug;
     e[e[i].pair].cap+=aug;
     if(d[now]<min_d[e[i].lab]) min_d[e[i].lab]=d[now];
   }
   else{
       if(--v[d[now]]==0) d[s]=tot;
       d[now]=min_d[now]+1;
       cur[now]=c[now];
       min_d[now]=tot-1;
       v[d[now]]++; 
   }
}

int main(){   
 scanf("%ld",&tt);
 while(tt--){
   scanf("%ld%ld",&n,&m);
   s=0;t=n+m+1;tot=t+1;
   sum=0;
   memset(c,0,sizeof(c));
   point=0;
   for(long i=1;i<=n;++i){
    scanf("%ld",&x);
    add(i,t,x,0);
   }
   for(long i=1;i<=m;++i){
    scanf("%ld%ld%ld",&ai,&bi,&ci);
    sum+=ci;
    add(n+i,ai,INF,0);
    add(n+i,bi,INF,0);
    add(s,n+i,ci,0);
   }
   memset(d,0,sizeof(d));
   memset(v,0,sizeof(v));
   v[0]=tot;
   flow=0;
   for(long i=0;i<=t;++i){
     cur[i]=c[i];
     min_d[i]=tot-1;
   }
   while(d[s]<tot){
     found=false;
     aug=INF;
     augment(s);
   }
   printf("%ld\n",sum-flow);
 }
 return 0;
}




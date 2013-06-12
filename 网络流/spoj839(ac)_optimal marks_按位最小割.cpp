#include<iostream>

using namespace std;

const long Max_N=505;
const long INF=0x7fffffff;

long g[Max_N][Max_N],c[Max_N],mark[Max_N],ans[Max_N],visit[Max_N],tag[Max_N];
long v[Max_N],d[Max_N],flow,aug,point;

struct edge{
  long lab,cap,next,pair;
}e[7005];

long tt,n,m,a,b,k,u,p,cur,s,t,tot;
bool found;

void augment(long now){
  if(d[s]>=tot) return;
  long i,min_d=tot-1,tmp=aug;
  if(now==t){
    found=true;
    return;
  }
  i=c[now];
  while(i){
   if(e[i].cap){
     if(d[now]==d[e[i].lab]+1){
       if(e[i].cap<aug) aug=e[i].cap;
       augment(e[i].lab);
       if(found) break;
       if(d[s]>=tot) return;
       aug=tmp;
     }
     if(d[e[i].lab]<min_d) min_d=d[e[i].lab];
   }
   i=e[i].next;
  }
   if(found){
     e[i].cap-=aug;
     e[e[i].pair].cap+=aug;
   }
   else{
     if(--v[d[now]]==0) d[s]=tot;
     d[now]=min_d+1;
     v[d[now]]++;
   }
}

void dfs(long now){
  visit[now]=1;
  ans[now]+=cur;
  long i=c[now];
  while(i>0){
   if(e[i].cap&&visit[e[i].lab]==0)
    dfs(e[i].lab);
   i=e[i].next;
  }
}

void add(long a,long b,long x,long y){
  point++;e[point].lab=b;e[point].cap=x;e[point].next=c[a];e[point].pair=point+1;c[a]=point;
  point++;e[point].lab=a;e[point].cap=y;e[point].next=c[b];e[point].pair=point-1;c[b]=point;
}

int main(){

 scanf("%ld",&tt);
 
 while(tt--){
  memset(g,0,sizeof(g));
  scanf("%ld%ld",&n,&m);
  for(long i=1;i<=m;++i){
    scanf("%ld%ld",&a,&b);
    if(a<b) g[a][b]++;
     else g[b][a]++;
  }
  scanf("%ld",&k);
  memset(mark,0,sizeof(mark));
  memset(ans,0,sizeof(ans));
  memset(tag,0,sizeof(tag));
  for(long i=1;i<=k;++i){
    scanf("%ld%ld",&u,&p);
    mark[u]=p;
    tag[u]=1;
  }
  cur=1;
  s=0;t=n+1;tot=t+1;
  for(long k=1;k<=31;++k){
    memset(c,0,sizeof(c));
    point=0;
    for(long i=1;i<=n;++i)
     for(long j=1;j<=n;++j)
      if(g[i][j])
         add(i,j,g[i][j],g[i][j]);                 
   for(long i=1;i<=n;++i)
    if(tag[i]){
      if(mark[i]%2==0) add(i,t,INF,0);
      else add(s,i,INF,0);
      mark[i]/=2;
    }
   memset(v,0,sizeof(v));
   memset(d,0,sizeof(d));
   v[0]=tot;
   while(d[s]<tot){
     aug=INF;
     found=false;
     augment(s);
   }
   memset(visit,0,sizeof(visit));
   dfs(s);
   if(k!=31) cur*=2;
  }
  for(long i=1;i<=n;++i) 
    printf("%ld\n",ans[i]);
 }
 return 0;
}

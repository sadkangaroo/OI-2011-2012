#include<iostream>
#include<math.h>
#include<queue>

using namespace std;

const long Max_N=105;
const long Max_M=105;
const long INF=0x7fffffff;

struct a_bulding{
  long x,y,num;
}building[Max_N];

struct a_shelter{
  long x,y,cap;
}shelter[Max_M];

long n,m,eij,t,now;
long cap[Max_N+Max_M+5][Max_N+Max_M+5],cost[Max_N+Max_M+5][Max_N+Max_M+5];
long dis[Max_N+Max_M+5],flag[Max_N+Max_M+5],cnt[Max_N+Max_M+5],pre[Max_N+Max_M+5];
queue <long> q;
bool f;

void spfa(){
  memset(dis,0,sizeof(dis));
  memset(flag,true,sizeof(flag));
  memset(cnt,0,sizeof(cnt));
  while(!q.empty()) q.pop();
  for(long i=0;i<=n+m;++i) q.push(i);
  f=true;
  long i;
  while(!q.empty()&&f){
   now=q.front();
   q.pop();
   flag[now]=false;
   for(i=0;i<=n+m;++i)
    if(cap[now][i]){
      if(dis[now]+cost[now][i]<dis[i]){
        dis[i]=dis[now]+cost[now][i];
        pre[i]=now;
        if(!flag[i]){
          q.push(i);
          cnt[i]++;
          if(cnt[i]>=n+m+1){
            f=false;
            break;
          }
          flag[i]=true;
        }
      }
    }
  }
  memset(flag,false,sizeof(flag));
  while(!flag[i]){
    flag[i]=true;
    i=pre[i];
  }
  memset(flag,false,sizeof(flag));
  while(!flag[i]){
    flag[i]=true;
    cap[pre[i]][i]--;
    cap[i][pre[i]]++;
    i=pre[i];
  }
  if(f) printf("OPTIMAL\n");
   else{
     printf("SUBOPTIMAL\n");
     for(long i=1;i<=n;++i)
     for(long j=1;j<=m;++j){
       if(j!=1) printf(" ");
       printf("%ld",INF-cap[i][n+j]);
       if(j==m) printf("\n");
     }
   }
}

int main(){
  scanf("%ld%ld",&n,&m);
  t=0;
  memset(cost,0,sizeof(cost));
  memset(cap,0,sizeof(cap));
  for(long i=1;i<=n;++i)
    scanf("%ld%ld%ld",&building[i].x,&building[i].y,&building[i].num);
  for(long i=1;i<=m;++i){
    scanf("%ld%ld%ld",&shelter[i].x,&shelter[i].y,&shelter[i].cap);
    cap[n+i][t]=shelter[i].cap;
  }
  for(long i=1;i<=n;++i)
   for(long j=1;j<=m;++j){
     cap[i][n+j]=INF;
     cost[i][n+j]=abs(building[i].x-shelter[j].x)+abs(building[i].y-shelter[j].y)+1;
     cost[n+j][i]=-cost[i][n+j];
   }
  for(long i=1;i<=n;++i)
   for(long j=1;j<=m;++j){
     scanf("%ld",&eij);
     cap[i][n+j]-=eij;
     cap[n+j][i]+=eij;
     cap[n+j][t]-=eij;
     cap[t][n+j]+=eij;
   }
  spfa(); 
  return 0;
}

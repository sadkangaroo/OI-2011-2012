#include<iostream>

using namespace std;

const long Max_N=210;
const long INF=0X7fffffff;

struct node{
  double x,y;
  long num,times;
}pg[Max_N];

long n,s,t,aug,flow,tot,ni,mi,tc;
long c[Max_N][Max_N],v[Max_N],d[Max_N];
bool found,flag;
double dis,xi,yi;

void augment(long now){
  if(d[s]>=2*n+1) return;
  long i,tmp=aug,min_d=2*n;
  if(now==t){
    found=true;
    flow+=aug;
    return;
  }
  for(i=1;i<=2*n;++i){
    if(c[now][i]){
     if(d[now]==d[i]+1){
       if(c[now][i]<aug) aug=c[now][i];
       augment(i);
       if(d[s]>=2*n+1) return;
       if(found) break;
       aug=tmp;
     }     
     if(d[i]<min_d) min_d=d[i];;
    }
  }
  if(found){
    c[now][i]-=aug;
    c[i][now]+=aug;
  }
  else{
    if(--v[d[now]]==0) d[s]=2*n+1;
    d[now]=min_d+1;
    v[d[now]]++;
  }
}

int main(){
    
  scanf("%ld",&tc);
  for(long i_tc=1;i_tc<=tc;++i_tc){
    scanf("%ld%lf",&n,&dis);
    tot=0;
    for(long i=1;i<=n;++i){
      scanf("%lf%lf%ld%ld",&xi,&yi,&ni,&mi);
      pg[i].x=xi;pg[i].y=yi;pg[i].num=ni;pg[i].times=mi;
      tot+=ni;
    }
    s=0;
    flag=false;
    for(long k=1;k<=n;++k){
      t=2*k-1;
      memset(c,0,sizeof(c));
      for(long i=1;i<=n;++i){
        c[s][2*i-1]=pg[i].num;
        c[2*i-1][2*i]=pg[i].times;
        for(long j=1;j<=n;++j){
          if(i!=j){
            if(dis*dis>=(pg[i].x-pg[j].x)*(pg[i].x-pg[j].x)+(pg[i].y-pg[j].y)*(pg[i].y-pg[j].y))
              c[2*i][2*j-1]=c[2*j][2*i-1]=INF;
          }
        }
      }  
      memset(v,0,sizeof(v));
      memset(d,0,sizeof(d));
      v[0]=2*n+1;
      flow=0;
      while(d[s]<2*n+1){
        found=false;
        aug=INF;
        augment(s);
      }
      if(flow==tot){
        if(!flag) {printf("%ld",k-1);flag=true;}
         else printf(" %ld",k-1);
      }
      
    }
    if(flag==false) printf("-1\n");
     else printf("\n");
  }
  return 0;
}

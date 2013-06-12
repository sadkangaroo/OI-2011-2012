#include<iostream>

using namespace std;

const long Max_N=103;
const long INF=0x7fffffff;

long gback[Max_N][Max_N],v[Max_N],d[Max_N],flag[Max_N],lab[Max_N][Max_N];
double c[Max_N][Max_N];
double flow,aug;
bool found,first,first2;

long n,m,a,b,x,tot;
double lef,rig,mid;

void augment(long now){
  if(d[1]>=n) return;
  long min_d=n,i; double tmp=aug;
  if(now==n){
    found=true;
    flow+=aug;
    return;
  }
  for(i=1;i<=n;++i)
   if(c[now][i]>0){
     if(d[now]==d[i]+1){
       if(c[now][i]<aug) aug=c[now][i];
       augment(i);
       if(found) break;
       if(d[1]>=n) return;
       aug=tmp;
     }
     if(d[i]<min_d) min_d=d[i];
   }
  if(found){
    c[now][i]-=aug;
    c[i][now]+=aug;
  }
  else{
    if(--v[d[now]]==0) d[1]=n;
    d[now]=min_d+1;
    v[d[now]]++;
  }
}

double check(double ans){
  double ret=0;
  for(long i=1;i<=n;++i)
   for(long j=1;j<=n;++j){
     if(c[i][j]>0) c[i][j]-=ans;
     if(c[i][j]<0&&i>=j) ret+=c[i][j];
   }
  memset(v,0,sizeof(v));
  memset(d,0,sizeof(d));
  v[0]=n;
  flow=0;
  while(d[1]<n){
    found=false;
    aug=INF;
    augment(1);
  }
  ret+=flow;
  return ret;
}

void sep(long now){
  if(flag[now]==1) return;
  flag[now]=1;
  for(long i=1;i<=n;++i)
    if(c[now][i]>0)
     sep(i);
}

int main(){

 first=true;
 while(scanf("%ld%ld",&n,&m)!=EOF){
  memset(gback,0,sizeof(gback));
  memset(lab,0,sizeof(lab));
  for(long i=1;i<=m;++i){
    scanf("%ld%ld%ld",&a,&b,&x);
    gback[a][b]=gback[b][a]=x;
    lab[a][b]=lab[b][a]=i;
  }  
  lef=0;rig=10000000;
  while(lef+0.000001<rig){
    for(long i=1;i<=n;++i) for(long j=1;j<=n;++j) c[i][j]=gback[i][j];
    mid=(lef+rig)/2;
    double ch=check(mid);
    if(ch<0) rig=mid;
     else if(ch>0) lef=mid;
      else break;
  }
  memset(flag,0,sizeof(flag));
  sep(1);
  tot=0;
  for(long i=1;i<=n;++i)
   for(long j=1;j<=n;++j)
    if(c[i][j]<0&&i>=j||c[i][j]>=0&&gback[i][j]>0&&flag[i]==1&&flag[j]==0)
     tot++;
  if(first) first=false;
   else printf("\n");
  printf("%ld\n",tot);
  first2=true;
  for(long i=1;i<=n;++i)
   for(long j=1;j<=n;++j)
    if(c[i][j]<0&&i>=j||c[i][j]>=0&&gback[i][j]>0&&flag[i]==1&&flag[j]==0){
     if(first2) first2=false;
      else printf(" ");
      printf("%ld",lab[i][j]);
    }
  if(first2!=true) printf("\n");
 } 
 return 0;
}

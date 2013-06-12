#include<iostream>

using namespace std;

const long Max_N=20005;
const long INF=0x7fffffff;

struct node{
  long lable,value,next,pair;
}e[500003];

long n,m,s,t,aug,flow,point;
long c[Max_N],v[Max_N],d[Max_N],cur[Max_N],min_d[Max_N];
bool found;

void augment(long now){
  if(d[s]>=n) return;
  long tmp=aug,i;
  if(now==t){
    found=true;
    flow+=aug;
    return;
  }
  i=cur[now];
  while(i){
    if(e[i].value){
      if(d[now]==d[e[i].lable]+1){
        cur[now]=i;
        if(e[i].value<aug) aug=e[i].value;
        augment(e[i].lable);
        if(d[s]>=n) return;
        if(found) break;
        aug=tmp;
      }
    if(d[e[i].lable]<min_d[now]) min_d[now]=d[e[i].lable];
    }
    i=e[i].next;
  }
  if(found){
    e[i].value-=aug;
    e[e[i].pair].value+=aug;
    if(d[now]<min_d[e[i].lable]) min_d[e[i].lable]=d[now];
  }
  else{
    if(--v[d[now]]==0) d[s]=n;
    cur[now]=c[now];
    d[now]=min_d[now]+1;
    min_d[now]=n-1;
    v[d[now]]++;
  }
}

void add(long a,long b,long x,long y){
  point++;e[point].lable=b;e[point].value=x;e[point].pair=point+1;e[point].next=c[a];c[a]=point;
  point++;e[point].lable=a;e[point].value=y;e[point].pair=point-1;e[point].next=c[b];c[b]=point;
}

int main(){

  scanf("%ld%ld",&n,&m);
  n+=2;
  s=n-1;t=n;
  memset(c,0,sizeof(c));
  point=0;
  long ai,bi;
  for(long i=1;i<=n-2;++i){
    scanf("%ld%ld",&ai,&bi); 
    add(s,i,ai,0);
    add(i,t,bi,0);
  } 
  long a,b,w;
  for(long i=1;i<=m;++i){
    scanf("%ld%ld%ld",&a,&b,&w);
    add(a,b,w,w);
  }
  memset(d,0,sizeof(d));
  memset(v,0,sizeof(v));
  v[0]=n;
  flow=0;
  for(long i=1;i<=n;++i){
    cur[i]=c[i];
    min_d[i]=n-1;
  }       
  while(d[s]<n){
    aug=INF;            
    found=false;
    augment(s);
  }
  printf("%ld\n",flow);
  return 0;
}


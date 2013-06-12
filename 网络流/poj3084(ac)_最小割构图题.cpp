#include<iostream>

using namespace std;

const long Max_N=23;
const long INF=20000003;

long dataset,m,n,s,t,k,p,flow,aug;
long c[Max_N][Max_N],v[Max_N],d[Max_N];
char ch;
bool found;

void augment(long now){
  if(d[s]>=m+1) return;
  long tmp=aug,min_d=m,i;
  if(now==t){
    found=true;
    flow+=aug;
    return;
  }
  for(i=0;i<=m;++i){
    if(c[now][i]){
      if(d[now]==d[i]+1){
        if(c[now][i]<aug) aug=c[now][i];
        augment(i);
        if(d[s]>=m+1) return;
        if(found) break;
        aug=tmp;
      }
      if(d[i]<min_d) min_d=d[i];
    }
  }
  if(found){
    c[now][i]-=aug;
    c[i][now]+=aug;
  }
  else{
    if(--v[d[now]]==0) d[s]=m+1;
    d[now]=min_d+1;
    v[d[now]]++;
  }
}

int main(){
  scanf("%ld\n",&dataset);
  for(long i_ds=1;i_ds<=dataset;++i_ds){
    scanf("%ld %ld\n",&m,&n);
    memset(c,0,sizeof(c));
    s=m;t=n;
    for(long i=0;i<m;++i){
      scanf("%c",&ch);
      if(ch=='I'){
        scanf(" ");
        c[s][i]=INF;  
      }
      else scanf("I "); 
      scanf("%ld",&k);
      for(long j=1;j<=k;++j){
          scanf(" %ld",&p);
          c[i][p]=INF;
          c[p][i]+=1;
      }
      scanf("\n");
    }
    flow=0;
    memset(v,0,sizeof(v));
    memset(d,0,sizeof(d));
    v[0]=m+1;
    while(d[s]<m+1){
      found=false;
      aug=INF;
      augment(s);
    }
    if(flow>=INF) printf("PANIC ROOM BREACH\n");
     else printf("%ld\n",flow);
  }
  return 0;
}

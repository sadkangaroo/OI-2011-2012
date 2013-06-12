#include<iostream>

using namespace std;

const long Max_N=65;
const long INF=0x7fffffff;

long cases,n,s,t,totn,flow,aug,cur,sum;
long a[13],c[Max_N][Max_N],v[Max_N],d[Max_N];
char ch;
bool found;

void augment(long now){
  if(d[s]>=totn) return;
  long i,tmp=aug,min_d=totn-1;
  if(now==t){
    flow+=aug;
    found=true;
    return; 
  }
  for(i=1;i<=t;++i){
    if(c[now][i]){
      if(d[now]==d[i]+1){
       if(c[now][i]<aug) aug=c[now][i];
       augment(i);
       if(found) break;
       if(d[s]>totn) return;
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
    if(--v[d[now]]==0) d[s]=totn;
    d[now]=min_d+1;
    v[d[now]]++;
  }
}

int main(){
   scanf("%ld",&cases);
   while(scanf("%c",&ch)&&ch!='\n');
   while(cases--){
     n=0;sum=0;
     while(scanf("%c",&ch)&&ch!='\n')
      if(ch>='0'&&ch<='9'){
        n++;
        a[n]=ch-'0';
        sum+=a[n];
      }
     s=0;
     t=n*(n-1)/2+n+1;
     totn=t+1;
     for(long k=1;k<=n;++k){
        memset(c,0,sizeof(c));
        for(long i=1;i<=n;++i)
          c[s][i]=a[i]; 
        for(long i=n+1;i<t;++i)
          c[i][t]=1;
        cur=n;
        for(long i=1;i<=n;++i)
         for(long j=i+1;j<=n;++j){
           cur++;
           c[i][cur]=1;
           c[j][cur]=1;
           if(i>=k&&a[j]>a[i]) c[j][cur]=0;
         } 
       flow=0;
       memset(v,0,sizeof(v));
       memset(d,0,sizeof(d));
       v[0]=totn;
       while(d[s]<totn){
         aug=INF;
         found=false;
         augment(s);
       }
       if(flow==sum){
         printf("%ld\n",n-k+1);
         break;
       } 
     }
   }
   return 0;
}

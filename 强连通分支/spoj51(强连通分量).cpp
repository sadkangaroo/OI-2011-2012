#include<iostream>
#include<vector>

using namespace std;

const long Max_N=1003;

long t,n,m,x,cur,trec,low,tot;
long a[Max_N],belong[Max_N],visit[Max_N],newg[Max_N][Max_N],num[Max_N],into[Max_N];
vector <long> rec;
vector <long> g1[Max_N],g2[Max_N];

void dfs(long now){
  rec.push_back(now);
  visit[now]=1;
  for(long i=0;i<g1[now].size();++i)
   if(visit[g1[now][i]]==0)
    dfs(g1[now][i]);
  trec++;
  a[now]=trec;
}

void dfs2(long now){
  visit[now]++;
  belong[now]=cur;
  num[cur]++;
  for(long i=0;i<g2[now].size();++i)
   if(visit[g2[now][i]]==1&&a[g2[now][i]]>low)
    dfs2(g2[now][i]);
}

int main(){  

  scanf("%ld",&t);
  while(t--){
   for(long i=1;i<=n;++i){
     g1[i].clear();
     g2[i].clear();
   }
   scanf("%ld",&n);
   for(long i=1;i<=n;++i){
     scanf("%ld",&m);
     for(long j=1;j<=m;++j){
      scanf("%ld",&x);
      g1[x].push_back(i);
      g2[i].push_back(x);
     }
   }
   trec=0;
   cur=0;
   memset(a,0,sizeof(a));
   memset(belong,0,sizeof(belong));
   memset(visit,0,sizeof(visit));
   memset(num,0,sizeof(num));

   for(long k=1;k<=n;++k)
    if(visit[k]==0){
      rec.clear();
      low=trec;

      dfs(k);
      sort(rec.begin(),rec.end(),greater<long>());   
      while(!rec.empty()){
        if(visit[rec.back()]==1){
          cur++;
          dfs2(rec.back());
        }
        rec.pop_back();
      }
    }
   tot=cur;
   memset(newg,0,sizeof(newg));
   for(long i=1;i<=n;++i)
    for(long j=0;j<g1[i].size();++j)
     if(belong[i]!=belong[g1[i][j]])
      newg[belong[i]][belong[g1[i][j]]]=1;
   memset(into,0,sizeof(into));
   for(long i=1;i<=tot;++i)
    for(long j=1;j<=tot;++j)
     if(newg[j][i]) into[i]++;
   bool flag=false;
   long pos;
   for(long i=1;i<=tot;++i)
    if(into[i]==0){
     if(flag==false) {flag=true;pos=i;}
     else {flag=false;break;}
    } 
    if(flag) printf("%ld\n",num[pos]);
     else printf("0\n");
  }  
  return 0;
}

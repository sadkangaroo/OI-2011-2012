/*
题目大意：将一张图进行强连通缩点后 1)有多少个入度为0的点 2)至少再添几条边能变成强连通图
算法思路：用korasaju进行强连通缩点，然后统计入度为0的点的个数ans1与出度为0的点的个数ans2
第一问输出ans1，第二问输出max(ans1,ans2)
***特别注意！：当只有一个强连通块，即缩点后只有一个点时，第二问输出0！***
对于第二问的证明:首先容易证明ans>=ans1且ans>=ans2，
下面证明，添加max(ans1,ans2)条边是可以将其变成强连通图的
设入度为零的点为A类节点，出度为零的节点为B类节点，若一个A节点与一个B节点有路径则将点对（A，B）添加到集合S，
先取出集合中的一个点对放入集合T，接下来依次对S集合中的点对：若点对(A,B）中有点在T中出现过，则放入集合R，
否则将上一次放入T的B'节点与此A节点间连一条边将（B',A）放入T，一直到S集合中无点对可取，
此时T集合中的点对组成一条链，再添一条边使这条链首尾相连，形成环W，R中的点对要么进入S要么从S出来，任意配对连边，
多出的 点对任意连入环中，此时原图中所有点要么在环中，要么既可以进入环又可以从环中出来，因此此时环强连通，
（非A、B类节点一定与A、B类节点都相连，因为是有向无环图）
又注意到此过程中入/出度为零的边只会连一次，而在配对结束前每次都是出度为零的点连上入度为零的点，
因此添加了max(ans1,ans2)条边; 
*/
#include<iostream>
#include<math.h>
#include<string>
using namespace std;

long g[105][105],gr[105][105],vis[105],order[105],in_set[105],into[105],outof[105];
long n,p,cnt,x,ans1,ans2;

void dfs(long cur){
  for(long i=1;i<=n;++i)
   if(g[cur][i]&&vis[i]==0){
     vis[i]=1;
     dfs(i);
   }
   order[++p]=cur;
}

void rdfs(long cur){
  in_set[cur]=cnt;
  for(long i=1;i<=n;++i)
   if(gr[cur][i]&&vis[i]==0){
     vis[i]=1;
     rdfs(i);
   }
}

void korasaju(){
  memset(vis,0,sizeof(vis));
  for(long k=1;k<=n;++k)
    if(vis[k]==0){
      vis[k]=1;
      dfs(k);
    }
  memset(vis,0,sizeof(vis));
  cnt=0;
  for(long k=p;k>=1;--k){
    if(vis[order[k]]==0){
      cnt++;
      vis[order[k]]=1;
      rdfs(order[k]);
    }
  }
}

int main(){
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  scanf("%ld",&n);
  memset(g,0,sizeof(g));
  memset(gr,0,sizeof(gr));
  for(long i=1;i<=n;++i)
    while(scanf("%ld",&x)&&x!=0){
      g[i][x]=1;
      gr[x][i]=1;
    }
  p=0;
  korasaju();
  memset(into,0,sizeof(into));
  memset(outof,0,sizeof(outof));
  for(long i=1;i<=n;++i)
   for(long j=1;j<=n;++j)
    if(g[i][j]&&in_set[i]!=in_set[j]){
      outof[in_set[i]]=1;
      into[in_set[j]]=1;
    }
  ans1=ans2=0;
  for(long i=1;i<=cnt;++i){
    if(into[i]==0) ans1++;
    if(outof[i]==0) ans2++;
  }
  printf("%ld\n",ans1);
  if(cnt==1)printf("0\n");
  else{
  if(ans1>ans2) printf("%ld\n",ans1);
   else printf("%ld\n",ans2);
  }
  return 0;
}

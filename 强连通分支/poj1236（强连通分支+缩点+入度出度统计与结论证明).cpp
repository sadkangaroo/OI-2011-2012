/*
��Ŀ���⣺��һ��ͼ����ǿ��ͨ����� 1)�ж��ٸ����Ϊ0�ĵ� 2)�������������ܱ��ǿ��ͨͼ
�㷨˼·����korasaju����ǿ��ͨ���㣬Ȼ��ͳ�����Ϊ0�ĵ�ĸ���ans1�����Ϊ0�ĵ�ĸ���ans2
��һ�����ans1���ڶ������max(ans1,ans2)
***�ر�ע�⣡����ֻ��һ��ǿ��ͨ�飬�������ֻ��һ����ʱ���ڶ������0��***
���ڵڶ��ʵ�֤��:��������֤��ans>=ans1��ans>=ans2��
����֤�������max(ans1,ans2)�����ǿ��Խ�����ǿ��ͨͼ��
�����Ϊ��ĵ�ΪA��ڵ㣬����Ϊ��Ľڵ�ΪB��ڵ㣬��һ��A�ڵ���һ��B�ڵ���·���򽫵�ԣ�A��B����ӵ�����S��
��ȡ�������е�һ����Է��뼯��T�����������ζ�S�����еĵ�ԣ������(A,B�����е���T�г��ֹ�������뼯��R��
������һ�η���T��B'�ڵ����A�ڵ����һ���߽���B',A������T��һֱ��S�������޵�Կ�ȡ��
��ʱT�����еĵ�����һ����������һ����ʹ��������β�������γɻ�W��R�еĵ��Ҫô����SҪô��S����������������ߣ�
����� ����������뻷�У���ʱԭͼ�����е�Ҫô�ڻ��У�Ҫô�ȿ��Խ��뻷�ֿ��Դӻ��г�������˴�ʱ��ǿ��ͨ��
����A��B��ڵ�һ����A��B��ڵ㶼��������Ϊ�������޻�ͼ��
��ע�⵽�˹�������/����Ϊ��ı�ֻ����һ�Σ�������Խ���ǰÿ�ζ��ǳ���Ϊ��ĵ��������Ϊ��ĵ㣬
��������max(ans1,ans2)����; 
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

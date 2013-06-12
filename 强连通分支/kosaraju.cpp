/*
ǿ��ͨ��֧��kosaraju�㷨
���ȶ�ԭͼ����dfs�����ڵ��ջ˳��������ڶԷ���ͼ����dfs��
ÿһ��dfs�õ�һ��ǿ��ͨ��֧���ҵõ���֧��˳��������˳�� 
*/
#include<iostream>
#include<math.h>
#include<string>
using namespace std;

long g[105][105],gr[105][105],vis[105],order[105],in_set[105];
long n,p,cnt;

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

void kosaraju(){
  p=0;
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
  return 0;
}

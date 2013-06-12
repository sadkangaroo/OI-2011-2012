/*

题目大意: 
我们已知n对夫妻的婚姻状况，称第i对夫妻的男方为Bi，女方为Gi。
若某男Bi与某女Gj曾经交往过（i≠j），
则当某方与其配偶（即Bi与Gi或Bj与Gj）感情出现问题时，他们有私奔的可能性。
不妨设Bi和其配偶Gi感情不和，于是Bi和Gj旧情复燃，进而Bj因被戴绿帽而感到不爽，
联系上了他的初恋情人Gk……一串串的离婚事件像多米诺骨牌一般接踵而至。
若在Bi和Gi离婚的前提下，这2n个人最终依然能够结合成n对情侣，
那么我们称婚姻i为不安全的，否则婚姻i就是安全的。
给定所需信息，你的任务是判断每对婚姻是否安全。

解题思路: 
新建一个有n个节点的图g
若Gi与Bj曾经搞过，g[i]向g[j]连一条边
第k号节点代表的婚姻不稳定等价于k号节点在一个节点数大于1的环中
那么只要对g做强连通分量，统计每对婚姻所在分量的节点数，若大于1则不稳定，否则稳定

*/


#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int Max_N=10010,Max_M=20010;

string s;
int vis[Max_N],order[Max_N],col[Max_N],sum[Max_N];
int n,m,p,to,key,lab1,lab2,cnt;

struct h_node{
  string s;
  int lab,lnk;
  h_node(){};
  h_node(string _s,int _lab,int _lnk){
    s=_s;lab=_lab;lnk=_lnk;
  }
}h_lnk[Max_N];int h_p=-1;
int hash[999983];

struct g_node{
  int to,lnk;
  g_node(){};
  g_node(int _to,int _lnk){to=_to;lnk=_lnk;}
}g_lnk[Max_M],rg_lnk[Max_M];int g_p=-1;int rg_p=-1;
int g[Max_N],rg[Max_N];;

void get_string(){
  char ch;s="";key=1;
  while(scanf("%c",&ch)&&ch!=' '&&ch!='\n'){
    s+=ch;
    key=key*31+ch;
  }
  key=(key&0x7fffffff)%999983;
}

void dfs(int now){
  for(int cur=g[now];cur!=-1;cur=g_lnk[cur].lnk){
    to=g_lnk[cur].to;
    if(!vis[to]){vis[to]=1;dfs(to);}
  }
  order[++p]=now;
}

void rdfs(int now){
  col[now]=cnt;
  sum[cnt]++;
  for(int cur=rg[now];cur!=-1;cur=rg_lnk[cur].lnk){
    to=rg_lnk[cur].to;
    if(!vis[to]){vis[to]=1;rdfs(to);}
  }
}

void ksrj(){ 
  p=0;
  memset(vis,0,sizeof(vis));
  for(int i=1;i<=n;++i)
   if(!vis[i]) {vis[i]=1;dfs(i);} 
  cnt=0;
  memset(vis,0,sizeof(vis));
  memset(sum,0,sizeof(sum));
  for(int i=p;i>=1;--i)
    if(!vis[order[i]]) {cnt++;vis[order[i]]=1;rdfs(order[i]);}
}

int main(){

  freopen("marriage.in","r",stdin);
  freopen("marriage.out","w",stdout);
  
  scanf("%d\n",&n);
  memset(hash,-1,sizeof(hash));
  for(int i=1;i<=n;++i)
    for(int j=1;j<=2;++j){
      get_string();//up date s and key
      h_lnk[++h_p]=h_node(s,i,hash[key]);
      hash[key]=h_p;
    }
  
  scanf("%d\n",&m);
  memset(g,-1,sizeof(g));
  memset(rg,-1,sizeof(rg));
  for(int i=1;i<=m;++i){
    get_string();
    for(int cur=hash[key];cur!=-1;cur=h_lnk[key].lnk)
      if(h_lnk[cur].s==s){lab1=h_lnk[cur].lab;break;}
    get_string();
    for(int cur=hash[key];cur!=-1;cur=h_lnk[key].lnk)
      if(h_lnk[cur].s==s){lab2=h_lnk[cur].lab;break;}
    if(lab1!=lab2){
      g_lnk[++g_p]=g_node(lab2,g[lab1]);
      g[lab1]=g_p;
      rg_lnk[++rg_p]=g_node(lab1,rg[lab2]);
      rg[lab2]=rg_p;
    }    
  }
  
  ksrj();
  
  for(int i=1;i<=n;++i)
    if(sum[col[i]]>1) printf("Unsafe\n");
      else printf("Safe\n");
  
  return 0;

}

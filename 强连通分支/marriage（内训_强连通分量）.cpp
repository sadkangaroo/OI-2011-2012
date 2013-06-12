/*

��Ŀ����: 
������֪n�Է��޵Ļ���״�����Ƶ�i�Է��޵��з�ΪBi��Ů��ΪGi��
��ĳ��Bi��ĳŮGj������������i��j����
��ĳ��������ż����Bi��Gi��Bj��Gj�������������ʱ��������˽���Ŀ����ԡ�
������Bi������żGi���鲻�ͣ�����Bi��Gj���鸴ȼ������Bj�򱻴���ñ���е���ˬ��
��ϵ�������ĳ�������Gk����һ����������¼������ŵ����һ����������
����Bi��Gi����ǰ���£���2n����������Ȼ�ܹ���ϳ�n�����£�
��ô���ǳƻ���iΪ����ȫ�ģ��������i���ǰ�ȫ�ġ�
����������Ϣ������������ж�ÿ�Ի����Ƿ�ȫ��

����˼·: 
�½�һ����n���ڵ��ͼg
��Gi��Bj���������g[i]��g[j]��һ����
��k�Žڵ����Ļ������ȶ��ȼ���k�Žڵ���һ���ڵ�������1�Ļ���
��ôֻҪ��g��ǿ��ͨ������ͳ��ÿ�Ի������ڷ����Ľڵ�����������1���ȶ��������ȶ�

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

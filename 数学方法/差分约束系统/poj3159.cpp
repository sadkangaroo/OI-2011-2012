/*
��Ŀ���⣺С���ѷ��ǣ���һЩ��ϵ��b���ǵĸ�������a���ǵĸ������ܴ���c��
Ҫ��С����n���Ǳ�С����1����������١�
��1��С����ΪԴ�㣬disֵ��Ϊ0����������n��С�����ǵ����ֵ�� 
�Ӷ��������Լ��ͼ����spfa+stack�����·�������һ����н�dis[i]��
�Ҵ�ʱÿ������ȡֵ�ﵽ���ֵ�����Դ�Ϊdis[n]�� 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const int Max_N=30005;
const int Max_E=150005;
const int oo=1<<30;

struct node{
  int to,cost,lnk;
  node(){};
  node(int _to,int _cost,int _lnk){ to=_to; cost=_cost; lnk=_lnk;}
}e[Max_E];
int point=-1;

int g[Max_N],s[Max_N];

int N,M,a,b,c,t,cost,to,f,r;
int dis[Max_N],vis[Max_N];

int main(){
  
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%d%d",&N,&M);
  
  memset(g,-1,sizeof(g));
  
  for(int i=1;i<=M;++i){
    scanf("%d%d%d",&a,&b,&c);
    e[++point]=node(b,c,g[a]);
    g[a]=point;
  }
  
  
  for(int i=2;i<=N;++i)
    dis[i]=oo;
  memset(vis,0,sizeof(vis));
  dis[1]=0;
  vis[1]=1;
    
  s[0]=1;
  r=0;
  
  while(r!=-1){
    t=s[r];
    vis[t]=0;
    r--;
    for(int cur=g[t];cur!=-1;cur=e[cur].lnk){
      cost=e[cur].cost;to=e[cur].to;
      if(dis[t]+cost<dis[to]){
        dis[to]=dis[t]+cost;
        if(!vis[to]){
          vis[to]=1;
          r++;
          s[r]=to;
        }
      }
    }
  }
  
  printf("%d\n",dis[N]);
  
  return 0;

}


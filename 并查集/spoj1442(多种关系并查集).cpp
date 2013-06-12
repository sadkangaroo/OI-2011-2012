#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<iterator>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<complex>

using namespace std;

const int Max_N=50005;

int T,N,K,o,x,y,fx,fy,sum;

struct node{int fa,rel;}a[Max_N];

int grand(int x){
  if(a[x].fa==x) return x;
  int oldfa=a[x].fa;
  a[x].fa=grand(a[x].fa);
  a[x].rel=(a[oldfa].rel+a[x].rel)%3;
  return a[x].fa;
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d",&T);
  while(T--){
    sum=0;
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;++i){
      a[i].fa=i;
      a[i].rel=0;
    }
    for(int i=1;i<=K;++i){
      scanf("%d%d%d",&o,&x,&y);
      if(o==2&&x==y){sum++;continue;}
      if(x>N||y>N){sum++;continue;}
      fx=grand(x);fy=grand(y);
      if(fx==fy){
        if(o==1){if(a[x].rel!=a[y].rel) sum++;}
        else{if((a[x].rel+3-a[y].rel)%3!=1) sum++;}
      }
      else{
        a[fy].fa=fx;
        if(o==1){a[fy].rel=(a[x].rel-a[y].rel+3)%3;}
        else{a[fy].rel=(a[x].rel-a[y].rel+2)%3;}
      }
    }
    printf("%d\n",sum);
  }

  return 0;

}

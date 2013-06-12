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

typedef long long LL;

const int Max_N=20005;

char c;
map<LL,int> id;
LL t;
int s[Max_N];
int N,M;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  while(scanf("%d%d\n",&N,&M)&&N){
    id.clear();               
    for(int i=1;i<=N;++i){
      t=0;
      for(int j=1;j<=M;++j){
        c=getchar();
        if(c=='A') t=t*4;
        if(c=='G') t=t*4+1;
        if(c=='C') t=t*4+2;
        if(c=='T') t=t*4+3;
      }
      getchar();
      if(!id.count(t)) id[t]=1;
        else id[t]++;
    }
    memset(s,0,sizeof(s));
    for(map<LL,int>::iterator iter=id.begin();iter!=id.end();++iter)
      s[iter->second]++;
    for(int i=1;i<=N;++i)
      printf("%d\n",s[i]);
  }

  return 0;

}

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<iterator>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<list>
#include<utility>
#include<complex>

using namespace std;

const int Max_N=305;

int a[Max_N][Max_N];
char buf[Max_N];
int T,N;

bool Even(){
  int j;
  for(int i=1;i<=N;++i){
    for(j=i;j<=N;++j)
      if(a[j][i]) break;
    if(j>N) return true;
    for(int k=1;k<=N;++k) swap(a[i][k],a[j][k]);
    for(int p=i+1;p<=N;++p)
      if(a[p][i])
        for(int q=i+1;q<=N;++q)
          if(a[i][q])
            a[p][q]=1-a[p][q];
  }
  return false;
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  scanf("%d",&T);
  while(T--){
    scanf("%d",&N);
    for(int i=1;i<=N;++i){
      scanf("%s",buf);
      for(int j=0;j<N;++j)
        a[i][j+1]=buf[j]-'0';
    }
    if(Even()) printf("Even\n");
      else printf("Odd\n");
  }

  return 0;

}

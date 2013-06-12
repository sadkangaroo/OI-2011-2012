/*
  2010/11/15
  floyd≈–∏∫ª∑
*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

typedef pair<string,int> pii;

const int Max_N=35;
const int oo=0x7fffffff;

vector<pii> hash[9983];
double g[Max_N][Max_N];
int N,M,key,cs;

int gethash(string &s){
  char ch;
  int h=37;
  s="";
  while((ch=getchar())&&ch!='\n'&&ch!=' '){
    h=(h+ch)*33;
    s+=ch;
  }
  return (h&0x7fffffff)%9983;
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  cs=0;
  while(scanf("%d\n",&N)&&N){
    cs++;
    for(int i=0;i<9983;++i)
      hash[i].clear();
    for(int i=1;i<=N;++i){
      string str;
      key=gethash(str);
      hash[key].push_back(make_pair(str,i));
    }
    for(int i=1;i<=N;++i)
      for(int j=1;j<=N;++j)
        g[i][j]=0;
    scanf("%d\n",&M);
    for(int i=1;i<=M;++i){
      string str;
      int a,b;
      key=gethash(str);
      for(int t=0;t<hash[key].size();++t){
        if(hash[key][t].first==str){
          a=hash[key][t].second;
        }
      }
      double rate;
      scanf("%lf ",&rate);
      key=gethash(str);
      for(int t=0;t<hash[key].size();++t){
        if(hash[key][t].first==str){
          b=hash[key][t].second;
        }
      }
      g[a][b]=rate;
    }
    for(int k=1;k<=N;++k)
      for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j){
          if(g[i][k]*g[k][j]>g[i][j])
            g[i][j]=g[i][k]*g[k][j];
        }
    bool flag=false;
    for(int i=1;i<=N;++i)
      if(g[i][i]>1) {flag=true; break;}
    if(flag) printf("Case %d: Yes\n",cs);
      else printf("Case %d: No\n",cs);
  }

  return 0;

}

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

using namespace std;

const int Max_N=105;
const int Hash_Mod=999983;

struct node{
  int x,p;
  node(){}
  node(int _x):x(_x),p(1){}
};

int a[Max_N];
vector<node> hash[Hash_Mod];
int N,t,pos,sum;

void search(int num){
  pos=abs(t%Hash_Mod);
  for(int i=0;i<hash[pos].size();++i)
    if(hash[pos][i].x==num){
      hash[pos][i].p++;
      return;
    }
  hash[pos].push_back(node(num));
}

void search2(int num){
  pos=abs(t%Hash_Mod);
  for(int i=0;i<hash[pos].size();++i)
    if(hash[pos][i].x==num){
      sum+=hash[pos][i].p;
      return;
    }
}

int main(){

  scanf("%d",&N);
  for(int i=1;i<=N;++i)
    scanf("%d",a+i);
  
  sum=0;
  for(int i=1;i<=N;++i)
    for(int j=1;j<=N;++j)
      for(int k=1;k<=N;++k){
        t=a[i]*a[j]+a[k];
        search(t);
      }
  for(int i=1;i<=N;++i)
    for(int j=1;j<=N;++j)
      for(int k=1;k<=N;++k)
        if(a[k]!=0){
          t=(a[i]+a[j])*a[k];
          search2(t);
        }
        
  printf("%d\n",sum);

  return 0;

}

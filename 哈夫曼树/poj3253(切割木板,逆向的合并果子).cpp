/*
 切割木板的方案对应一颗哈夫曼树，消耗的体力相当于最短带权路径和，利用堆构造哈夫曼树即可 
*/
#include<iostream>
#include<string>
#include<math.h>
#include<queue>
#include<vector>
using namespace std;

long long n,ans,x,tmp;

int main(){
  priority_queue< long long,vector<long long>,greater<long long> > a;
  scanf("%I64d",&n);
  for(long long i=1;i<=n;++i){
   scanf("%I64d",&x);
   a.push(x);
  }
  ans=0;
  for(long long i=1;i<=n-1;++i){
    tmp=a.top();a.pop();
    tmp+=a.top();a.pop();
    ans+=tmp;a.push(tmp);
  } 
  printf("%I64d\n",ans);
  return 0;
}

/*
 �и�ľ��ķ�����Ӧһ�Ź������������ĵ������൱����̴�Ȩ·���ͣ����öѹ�������������� 
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

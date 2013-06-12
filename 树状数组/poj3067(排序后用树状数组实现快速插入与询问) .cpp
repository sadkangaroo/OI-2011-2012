/*
��Ŀ���⣺
�����n��վ�㣬�ұ���m��վ�㣬����վ����и��ٹ�·������ÿ�������ٹ�·�Ľ��������Ե�λ���ã�
�����㹲�ߣ������ķ���
�㷨˼·:�Ƚ�k����·����˵�Ӵ�С������ͬ���Ҷ˵�Ӵ�С������˳���ǣ����ڵ�ǰ�ĸ��ٹ�·��
��֮ǰ���ǵĸ��ٹ�·����˵��Ŷ����ڵ�ǰ��·���Ҷ˵���С�ڵ�ǰ��·������Ե�λ���ã�
���������߶β���һ������ֻ��Ҫ����һ�Σ�����ÿ��ֻ����֮ǰ���߶�����Ľ��㣬
��֮ǰ�߶�����˵�������ͬ���Ҷ˵�һ���������Ҷ˵㣬 
����ֻ��Ҫά��1~k���Ҷ˵�Ŀǰ���˼�����·��������
1��ÿ�μ���һ����·ʱ���Ҷ˵�������·����һ 
2��ѯ��1~k���Ҷ˵�Ŀǰ���˼�����·
��������״����ʵ��ÿ�β���log���� 
*/
#include<iostream>
#include<string>
#include<math.h>
#include<algorithm>

using namespace std;

struct road{
  long long x,y;
  bool operator < (road const &t)const{
    if(x!=t.x) return x<t.x;
    return y<t.y;
  }
}a[1000005];

long long n,m,k,x,y,c[1005],ans,t;

void modify(long long p,long long del){
  for(;p<=n;p+=(p&(-p)))
    c[p]+=del;         //�޸�A[p]��ֵ 
}

long sum(long long p){
  long ret=0;
  for(;p>0;p-=(p&(-p)))        //��A����ǰp��� 
    ret+=c[p];
  return ret;
}

int main(){
  scanf("%I64d",&t);
  for(long long tt=1;tt<=t;++tt){
   scanf("%I64d%I64d%I64d",&n,&m,&k);
   for(long long i=1;i<=k;++i){
     scanf("%I64d%I64d",&x,&y);
     a[i].x=x;
     a[i].y=y;
   }
   sort(a+1,a+k+1);
   ans=0;
   memset(c,0,sizeof(c));
   for(long long i=k;i>=1;--i){
     if(a[i].y>1) ans+=sum((a[i].y)-1);  
     modify(a[i].y,1);     
   }
   printf("Test case %I64d: %I64d\n",tt,ans);
  }
  return 0;
}

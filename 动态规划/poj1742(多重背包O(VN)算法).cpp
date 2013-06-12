/*
多重背包的O（VN）简洁解法
ok[i]表示价值i是否可取到
last[i]表示价值i取到时用到编号最大的物品编号最小是多少
num[i]表示last[i]对应的物品取了至少多少个
上面的定义包含了贪心的思想
按顺序考虑每个物品
对每个物品考虑每个价值
若当前价值可以被取到，为了使当前价值取到时用到编号最大的物品编号最小，不更新
若不能被取到，则能更新的充要条件为 !(last[pre]==i&&num[pre]==c[i])
更新后，使当前价值j取到时用到编号最大的物品编号最小为i 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

const long Max_N=105,Max_M=100005;

int n,m,ans,pre,a[Max_N],ok[Max_M],c[Max_N],last[Max_M],num[Max_M];

int main(){
    
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  while(scanf("%d%d",&n,&m)&&(n||m)){
    for(int i=1;i<=n;++i)
      scanf("%d",a+i);
    for(int i=1;i<=n;++i)
      scanf("%d",c+i);
    memset(ok,0,sizeof(ok));
    ok[0]=1;
    ans=0;
    memset(last,0,sizeof(last));
    memset(num,0,sizeof(num));
    for(int i=1;i<=n;++i)
     for(int j=a[i];j<=m;++j)
       if(!ok[j]&&ok[pre=j-a[i]]&&!(last[pre]==i&&num[pre]==c[i])){
         ans++;
         ok[j]=1;
         last[j]=i;
         if(last[pre]==i) num[j]=num[pre]+1;
          else num[j]=1;
       }
    printf("%d\n",ans);
  }
}

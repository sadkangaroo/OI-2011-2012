/*
���ر�����O��VN�����ⷨ
ok[i]��ʾ��ֵi�Ƿ��ȡ��
last[i]��ʾ��ֵiȡ��ʱ�õ����������Ʒ�����С�Ƕ���
num[i]��ʾlast[i]��Ӧ����Ʒȡ�����ٶ��ٸ�
����Ķ��������̰�ĵ�˼��
��˳����ÿ����Ʒ
��ÿ����Ʒ����ÿ����ֵ
����ǰ��ֵ���Ա�ȡ����Ϊ��ʹ��ǰ��ֵȡ��ʱ�õ����������Ʒ�����С��������
�����ܱ�ȡ�������ܸ��µĳ�Ҫ����Ϊ !(last[pre]==i&&num[pre]==c[i])
���º�ʹ��ǰ��ֵjȡ��ʱ�õ����������Ʒ�����СΪi 
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

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>

using namespace std;

const int Mod=98765431;
const int Max_N=1005;

string _a,_b,_c,_d;
char str[Max_N];
int a[Max_N],b[Max_N],c[Max_N],d[Max_N];
int dp1[Max_N][12][2][2],dp2[Max_N][12][2][2][2];
int T,l1,l2;

int f2(int p,int last,int low,int high,int zero){
  if(last==10) return 0;
  if(p==l2) return 1; 
  int &ans=dp2[p][last][low][high][zero];
  if(ans!=-1) return ans;
  ans=0;
  if(zero&&c[p]==0){
    ans+=f2(p+1,last,low,high&(d[p]==0),zero);
    if(ans>=Mod) ans-=Mod;
  }
  if(!low||(low&&last>=c[p]))
    if(!high||(high&&last<=d[p])){
      ans+=f2(p+1,last,low&(last==c[p]),high&&(last==d[p]),zero&(last==0));
      if(ans>=Mod) ans-=Mod;
    }
  ans+=f2(p,last+1,low,high,0);
  if(ans>=Mod) ans-=Mod;
  return ans;
}

int f1(int p,int last,int low,int high){
  if(last==10) return 0;
  if(p==l1) return f2(0,last,1,1,1);
  int &ans=dp1[p][last][low][high];
  if(ans!=-1) return ans;
  ans=0;
  if(!low||(low&&last>=a[p]))
    if(!high||(high&&last<=b[p])){
      ans+=f1(p+1,last,low&(last==a[p]),high&&(last==b[p]));
      if(ans>=Mod) ans-=Mod;
    }
  ans+=f1(p,last+1,low,high);
  if(ans>=Mod) ans-=Mod;
  return ans;
}

void cv(string &s){
  scanf("%s",str);
  int p=0;s="";
  while(str[p]!='\0'){s+=str[p];p++;}
}

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  
  scanf("%d\n",&T);
  while(T--){
    cv(_a);cv(_b);cv(_c);cv(_d);
    while(_a.length()<_b.length()) _a='0'+_a;
    while(_c.length()<_d.length()) _c='0'+_c;
    l1=_a.length();l2=_c.length();
    for(int i=0;i<l1;++i){
      a[i]=_a[i]-'0';b[i]=_b[i]-'0';
    }
    for(int i=0;i<l2;++i){
      c[i]=_c[i]-'0';d[i]=_d[i]-'0';
    }
    memset(dp1,-1,sizeof(dp1));memset(dp2,-1,sizeof(dp2));
    printf("%d\n",f1(0,0,1,1));
  }
  
  return 0;

}

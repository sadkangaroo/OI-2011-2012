#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<math.h>

using namespace std;

const double eps=1e-7;
const int Max_N=100005,Max_xy=1005;

int T,N;
double sigmaxx,sigmayy,sigma2x,sigma2y,l,r,ll,rr,ansll,ansrr,tmp,ans;
int minx,maxx,miny,maxy,p0,p2;
int x[Max_N],y[Max_N],p[Max_N];

int main(){
    
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    
  scanf("%d",&T);
  while(T--){
    scanf("%d",&N);
	miny=minx=Max_xy;maxy=maxx=-Max_xy;
	p0=p2=0;
	sigmaxx=sigmayy=sigma2x=sigma2y=0;
    for(int i=1;i<=N;i++){
      scanf("%d%d%d",x+i,y+i,p+i);
	  if(x[i]>maxx) maxx=x[i];
	  if(x[i]<minx) minx=x[i];
      if(y[i]>maxy) maxy=y[i];
      if(y[i]<miny) miny=y[i];
	  if(p[i]==0) {p0++;i--;N--;continue;}
	  if(p[i]==2){
		p2++;
        sigmaxx+=x[i]*x[i];sigmayy+=y[i]*y[i];
	    sigma2x+=2*x[i];sigma2y+=2*y[i];
	    i--;N--;
	    continue;
	  }
	}
    l=minx;r=maxx;
    while(r-l>eps){
      ll=(2*l+r)/3.0;
      rr=(l+2*r)/3.0;
      ansll=ansrr=0;
      for(int i=1;i<=N;++i){
        if(p[i]==1){
          ansll+=fabs(ll-x[i]);
          ansrr+=fabs(rr-x[i]);
          continue;
        }
        tmp=fabs(ll-x[i]);
        ansll+=tmp*tmp*tmp;
        tmp=fabs(rr-x[i]);
        ansrr+=tmp*tmp*tmp;
      }
      ansll+=p2*ll*ll;
      ansll-=sigma2x*ll;
      ansrr+=p2*rr*rr;
      ansrr-=sigma2x*rr;
      if(ansll<ansrr) r=rr;
        else l=ll;
    }
	ans=(ansll+ansrr)/2.0;
    l=miny;r=maxy;
    while(r-l>eps){
      ll=(2*l+r)/3.0;
      rr=(l+2*r)/3.0;
      ansll=ansrr=0;
      for(int i=1;i<=N;++i){
        if(p[i]==1){
          ansll+=fabs(ll-y[i]);
          ansrr+=fabs(rr-y[i]);
          continue;
        }
        tmp=fabs(ll-y[i]);
        ansll+=tmp*tmp*tmp;
        tmp=fabs(rr-y[i]);
        ansrr+=tmp*tmp*tmp;
      }
      ansll+=p2*ll*ll;
      ansll-=sigma2y*ll;
      ansrr+=p2*rr*rr;
      ansrr-=sigma2y*rr;
      if(ansll<ansrr) r=rr;
        else l=ll;
    }
	ans+=((ansll+ansrr)/2.0);
	ans+=(2*p0+sigmaxx+sigmayy);
    printf("%.3lf\n",ans);
  }
  return 0;
}

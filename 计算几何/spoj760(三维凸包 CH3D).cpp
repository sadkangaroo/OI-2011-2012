#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iterator>
#include<vector>
#include<algorithm>

using namespace std;

const int Max_N=1005;
const double eps=1e-9;

bool hash[Max_N][Max_N];
double area,vol,t1,t2;
int T,N,a,b,c;

inline int dbc(double a,double b){return fabs(a-b)<eps?0:(a<b?-1:1);}

struct point{
  double x,y,z;  
  point(){}  
  point(double _x,double _y,double _z):x(_x),y(_y),z(_z){}  
  point operator + (const point &t)const{return point(x+t.x,y+t.y,z+t.z);}
  point operator - (const point &t)const{return point(x-t.x,y-t.y,z-t.z);}
  point operator / (double t)const{return(point(x/t,y/t,z/t));} 
  point operator * (const point &t)const{
    return point(y*t.z-z*t.y,z*t.x-x*t.z,x*t.y-y*t.x);
  } 
  double operator & (const point &t)const{return x*t.x+y*t.y+z*t.z;}
  double mod(){return sqrt(x*x+y*y+z*z);}
  void read(){scanf("%lf%lf%lf",&x,&y,&z);}
}idx[Max_N];

struct line{
  int a,b;
  line(){}
  line(int _a,int _b):a(_a),b(_b){}
};
vector<line> line_tmp;

struct face{
  int a,b,c;
  face(){}
  face(int _a,int _b,int _c):a(_a),b(_b),c(_c){};
  double area(){return ((idx[b]-idx[a])*(idx[c]-idx[a])).mod();}
  bool same_side(const point &p,const point &q){
    t1=(p-idx[a])&((idx[b]-idx[a])*(idx[c]-idx[a]));
    t2=(q-idx[a])&((idx[b]-idx[a])*(idx[c]-idx[a]));
    return dbc(t1*t2,0)>0;
  }
};
vector<face> face_tmp;vector<face> convex;

inline void deal(int a,int b){
  if(hash[a][b]) hash[a][b]=hash[b][a]=false;
    else hash[a][b]=hash[b][a]=true;
  line_tmp.push_back(line(a,b));
}

void CH3D(){
  for(int i=0;i<N;++i) idx[i].read();
  convex.clear();memset(hash,false,sizeof(hash));
  for(int i=0;i<4;++i) convex.push_back(face(i,(i+1)%4,(i+2)%4));
  point center=(idx[0]+idx[1]+idx[2]+idx[3])/4;
  for(int i=4;i<N;++i){
    line_tmp.clear();face_tmp.clear();
    for(int j=0;j<convex.size();++j){
      if(!convex[j].same_side(center,idx[i])){
        a=convex[j].a;b=convex[j].b;c=convex[j].c;
        deal(a,b);deal(b,c);deal(c,a);
      }
      else face_tmp.push_back(convex[j]);
    }
    convex.clear();
    for(int j=0;j<face_tmp.size();++j)
      convex.push_back(face_tmp[j]);
    for(int j=0;j<line_tmp.size();++j){
      a=line_tmp[j].a;b=line_tmp[j].b;
      if(hash[a][b]) convex.push_back(face(a,b,i));
      hash[a][b]=hash[b][a]=false;
    }
  }
  area=0;vol=0;
  for(int i=0;i<convex.size();++i){
    area+=convex[i].area();
    a=convex[i].a;b=convex[i].b;c=convex[i].c;
    vol+=fabs((idx[a]-center)&((idx[b]-center)*(idx[c]-center)))/6;
  }
  printf("%.2lf %.2lf\n",fabs(area*0.5),fabs(vol));
}

int main(){
  
  scanf("%d",&T);
  while(T--){
    scanf("%d",&N);
    CH3D();
  }

  return (0-0);

}

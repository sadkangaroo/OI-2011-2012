#include<iostream>
#include<string>
#include<math.h>
using namespace std;

/*

 并查集解决集合的合并与查询问题
*两项关键操作时间复杂度都是O(1)的 
*初始时每个元素各为一个集合,rank都赋为1（即每个集合高度为1）

*/
 
 long father[10003],rank[10003];
 
 //(1)查询元素x所属集合
 long grand(long x){
   if(father[x]==x) return x;
   father[x]=grand(father[x]);//重要优化：路径压缩
   return father[x]; 
 }
 //(2)合并两个集合
 void uni(long x,long y){
   long fx=grand(x),fy=grand(y);
   if(fx==fy) return;
   if(rank[fx]>rank[fy]) father[fy]=fx;//比较重要的优化：rank合并 
    else{
      father[fx]=fy;
      if(rank[fx]==rank[fy]) rank[fy]++;
    }
 } 

int main(){
  return 0;
}

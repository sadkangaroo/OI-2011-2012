/*
现有二次同余方程ax^2+bx+c=0(mod p) p不整除a；
两边同时乘以4a，同加上b^2，移项配方有（2ax+b)^2=b^2-4ac(mod p)
令y=2ax+b,d=b^2-4ac为常数，则只需讨论形如x^2=d（mod p)的同余方程，
注意到p整除d时，只有x=0（mod p）这一解，所以假定p不整除d
二次剩余：设p为奇素数，d为整数，p不整除d，
如果同余方程 x^2=d（mod p)有解，称d是模p的二次剩余（平方剩余），否则称非二次剩余
***在模p的一个简化剩余系（1~p-1）中，恰有（p-1)/2个模p的二次剩余，
（p-1)/2个模p的非二次剩余。
***若d是模p的二次剩余，p不整除d，则同余方程x^2=d（mod p)有且仅有两解x0与-x0
***欧拉判别法：设p为奇素数，p不整除d，
d是模p的二次剩余的充要条件为:d^[(p-1)/2]=1(mod p); 
d是模p的非二次剩余的充要条件为:d^[(p-1)/2]=-1(mod p);
***legendre符号（d/p)
=1：当d是模p的二次剩余
=-1：当d是模p的非二次剩余
=0： p整除d
***解同余方程x^2=d（mod p)：
当d是模p的二次剩余时  
(1)p为2， 易得
(2)p为奇素数，且p=4k+3,因为d是模p的二次剩余，所以有d^[2k+1]=1(mod p) 
即d^[2k+2]=d(mod p) 即 [d^(k+1)]^2=d(mod p) 所以x=+/- d^[(p+1)/4](mod p)
为其两解
(3)除了(1)(2)外化简后的同余方程或原同余方程若能在整数范围内因式分解，
则可将p标准分解枚举每个因子是否属于两个一次式，用拓展欧几里得求解二元一次不定方程 
*/
#include<iostream>
#include<string>
#include<math.h>
using namespace std;

int main(){

  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);

  return 0;

}

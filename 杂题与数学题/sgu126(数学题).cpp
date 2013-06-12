/*

两个桶里有A个和B个球，每次可以从一个桶放和另外一个桶中一样多的球到另外一个
桶中，问最少几次全移到一个桶
结论 若log（2）((A+B)/gcd(A+B))	为整数 则为答案，否则无解答
证明 首先对于一个二元组(p,q) 它与(p/gcd(p,q),q/gcd(p,q))是完全等价的
称互质的一个二元组为特征二元组。那么倒数第一步的特征二元组为(1,1)，设某一步的特征二元组为(m,n) (m,n)=1.那么它上一步的二元组可以为(m,2n+m)或(n,2m+n)
假设m+n=2^k 则m,n为奇数，则(m,2n)=1;(m,2n+m)=1;同理(n,2m+n)=1；所以它们都是上一步的特征二元组，且和为2^(k+1)，由数学归纳法，易得证。

*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

int a, b, t;

int gcd(int a,int b) {
    while (b) {t = a; a = b; b = t % b;}
    return a;
}

int main() {

    scanf("%d%d", &a, &b);
    if(a == 0 || b == 0) printf("0\n");
        else {
            int sum = (a + b) / gcd(a, b);
            int ans = (int)(log((double)(sum + 1))/log(2.0));
            if (1 << ans == sum) printf("%d\n", ans);
                else printf("-1\n");
        }
    
    return (0-0);

}

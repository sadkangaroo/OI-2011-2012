#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long LL;

const int MaxR = 65, MaxC = 105;

int R, C;
bool mat[MaxR][MaxC], use[MaxC];
LL x, ans;

void Init() {
    cin >> C; R = 1;
    memset(mat, 0, sizeof(mat));
    for (int j = 0; j < C; ++j) {
       cin >> x; int i = 0;
       for (; x; x >>= 1)
           mat[i++][j] = x & 1;
       if (i > R) R = i;
    }
    for (int i = 0; i < R; ++i)
        mat[i][C] = 1;
}

void Gauss() {
    memset(use, false, sizeof(use));
    for (int i = R - 1; i >= 0; --i) {
        ans <<= 1; int j;
        for (j = 0; j < C; ++j) 
            if (mat[i][j] && !use[j]) {
                use[j] = 1;
                ans |= 1;
                break;
            }
        if (j == C) {
            if (!mat[i][C]) 
                ans |= 1;
        }
        else {
            for (int k = i - 1; k >= 0; --k) 
                if (mat[k][j]) 
                    for (int s = 0; s <= C; ++s)
                        mat[k][s] ^= mat[i][s];
        }    
    }
}

int main() {
    
    Init();
    Gauss();
    cout << ans << endl;
    
    return 0;

}

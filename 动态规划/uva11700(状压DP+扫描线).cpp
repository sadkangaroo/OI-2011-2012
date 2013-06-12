#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int Max_R = 15, Max_C = 15, Max_State = 10005;

bool f[Max_State], fbak[Max_State] ,g[Max_R][Max_C][4];
char c, cc;
int R, C;

void Add(int x, int y, char d) {
    if (d == 'x') return;
    switch(d) {
        case 'E' : g[x][y][0] = true; break;
        case 'S' : g[x][y][1] = true; break;
        case 'W' : g[x][y][2] = true; break;
        case 'N' : g[x][y][3] = true; break;
    }
    return;
}

void rotate(int x, int y) {
    bool t = g[x][y][3];
    for (int i = 2; i >= 0; --i)
        g[x][y][i + 1] = g[x][y][i];
    g[x][y][0] = t;
}

void Init() {
    memset(g, false, sizeof(g));
    for (int i = 1; i <= R; ++i)
        for(int j = 1; j <= C; ++j)
            while (scanf("%c", &c) && c != ' ' && c != '\n')
                Add(i, j, c);
    memset(f, false, sizeof(f));
    for (int r = 1; r <= 4; ++r) {
        rotate(1, 1);
        if (!g[1][1][2] && !g[1][1][3])
            f[g[1][1][1] + g[1][1][0] * 2] = true;
    } 
}

bool OK(int x, int y, int d, int s, int p) {
    if (g[x][y][d] && (s & (1 << p))) return true;
    if (!g[x][y][d] && !(s & (1 << p))) return true;
    return false;
}

void update(int &s, int p, bool b) {
     if(b) s |= (1 << p);
         else s &= ~(1 << p);
}

void Solve() {
    for (int i = 1; i <= R; ++i) 
        for (int j = 1; j <= C; ++j) {
            memset(fbak, 0, sizeof(fbak));
            for (int k = 0; k < (1 << (C + 1)); ++k)
                if (f[k]) 
                    for (int r = 1; r <= 4; ++r) {
                        rotate(i, j);
                        if (j == 1){
                            if (i == 1) {
                                 memcpy(fbak, f, sizeof(f));
                                 continue;
                            }
                            if (k & (1 << C)) continue;
                            if (g[i][j][2]) continue;
                            if (!OK(i, j, 3, k, 0)) continue;
                            int t = k & ~(1 << C);
                            t <<= 1;
                            update(t, 0, g[i][j][1]);
                            update(t, 1, g[i][j][0]);
                            fbak[t] = true;
                            
                        }
                        else{
                            if (!OK(i, j, 2, k, j - 1)) continue;
                            if (!OK(i, j, 3, k, j)) continue;
                            int t = k;
                            update(t, j - 1, g[i][j][1]);
                            update(t, j, g[i][j][0]);
                            fbak[t] = true;
                        }  
                    }
            memcpy(f, fbak, sizeof(f));        
        }
}

void Answer() {
    if(f[0]) printf("SOLVABLE\n");
        else printf("UNSOLVABLE\n");
}

int main() {

    while (scanf("%d%c%d%c", &R, &c, &C, &cc) && R) {
        Init();
        Solve();
        Answer();
    }

    return (0-0);

}

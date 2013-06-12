#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int MaxState = 1005, MaxSize = 1005, Limit = 10000;

int N, M, X, Y;
int NextState[MaxState][2], Write[MaxState][2], Move[MaxState][2];
int tape[MaxSize];

void Init() {
    int q, c; char o;
    memset(NextState, -1, sizeof(NextState));
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &q, &c);
        scanf("%d%d %c", &NextState[q][c], &Write[q][c], &o);
        if (o == 'L') Move[q][c] = -1; else Move[q][c] = 1;
    }
}

void RunIt() {
    int p = 0, state = 0, step = 0, c; bool flag;
    while (++step <= Limit) {
        c = tape[p];
        if (NextState[state][c] == -1) break;
        tape[p] = Write[state][c];
        p += Move[state][c];
        state = NextState[state][c];
        if (p < 0 || p >= 1000) break;
    }
    if (step > Limit) puts("TLE");
    else if (p < 0 || p >= 1000) puts("MLE");
    else {
        flag = true;
        for (int i = 0; i < Y; ++i) if (!tape[i]) {flag = false; break;}
        for (int i = Y; i < MaxSize; ++i) if (tape[i]) {flag = false; break;}
        if (flag) puts("AC"); else puts("WA");
    } 
}

void Solve() {
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d", &X, &Y);
        memset(tape, 0, sizeof(tape));
        for (int k = 0; k < X; ++k) tape[k] = 1;
        RunIt();
    }
}

int main() {
    
    while (scanf("%d%d", &N, &M) && N) {
        Init();
        Solve();
    }
    
    return 0;

}

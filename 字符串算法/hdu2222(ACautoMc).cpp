#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>

using namespace std;

const int MaxN = 10000 + 5, MaxShortLen = 50 + 5, MaxLongLen = 1000000 + 5;
const int MaxNode = MaxN * MaxShortLen;

int T, N;
char str[MaxShortLen], s[MaxLongLen];

struct Node {
    Node *c[26], *f; int t;
    void* operator new(unsigned, void* p) {return p;}
    Node* rz(Node* fa) {f = fa; t = 0; return memset(c, 0, sizeof(c)), this;}
}trie[MaxNode], *cbuf, *root; queue<Node*> Q;

void Ins(Node* now, char* s) {
     for (int i = 0; s[i]; ++i) 
         if (now->c[s[i] - 'a']) now = now->c[s[i] - 'a'];
         else now = now->c[s[i] - 'a'] = (new(cbuf++)Node)->rz(now);
     now->t++;
}

void MakeFail() {
     Q.push(root); Node *u, *v;
     while (!Q.empty()) {
           u = Q.front(); Q.pop();
           for (int i = 0; i < 26; ++i) if (u->c[i]) {
               Q.push(u->c[i]); if (u == root) continue;
               v = u->f; while (v != root && !v->c[i]) v = v->f;
               if (v->c[i]) u->c[i]->f = v->c[i]; else u->c[i]->f = root;
           }
     }
}

int Match(Node* now, char* s) {
     int ret = 0; Node* d;
     for (int i = 0; s[i]; ++i) {
         while (now != root && !now->c[s[i] - 'a']) now = now->f;
         if (now->c[s[i] - 'a']) now = now->c[s[i] - 'a'];
         for (d = now; d != root && d->t != -1; d = d->f) 
             ret += d->t, d->t = -1;
     } return ret;
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);

    scanf("%d", &T);
    while (T--) {
          scanf("%d ", &N);
          cbuf = trie; root = (new(cbuf++)Node)->rz(NULL);
          while (N--) gets(str), Ins(root, str); 
          MakeFail(); gets(s);
          printf("%d\n", Match(root, s));
    }   

    return 0;

}

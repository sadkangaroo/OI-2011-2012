#include<iostream>
using namespace std;

const int MaxNode = 4500000 + 5, oo = 0x7fffffff / 4;
char o[20]; int N, M, t;

struct Node {
    int key, size, Same, sum, ml, mr, ms; Node* c[2]; bool rev;
    Node(): key(-oo), size(0), rev(0), Same(-oo), 
            sum(0), ml(-oo), mr(-oo), ms(-oo) {c[0] = c[1] = this;}
    Node(int _key, Node* _c0, Node* _c1): key(_key), rev(0), Same(-oo) {
        c[0] = _c0; c[1] = _c1;
    }
    void Paint() {sum = key * size; ml = mr = ms = max(key * size, key);}
    Node* pd(bool tag) {
        if (!size) return this;
        if (Same != -oo) {
           c[0]->key = c[0]->Same = c[1]->key = c[1]->Same = Same; 
           Same = -oo; Paint();
        }
        if (rev) {
           c[0]->rev ^= 1; c[1]->rev ^= 1; swap(c[0], c[1]);
           swap(ml, mr); rev = 0;
        }  
        if (c[0]->size && tag) c[0]->pd(0); if (c[1]->size && tag) c[1]->pd(0);
        return this;
    }
    Node* rz() {
        sum = c[0]->sum + c[1]->sum + key;
        ml = max(c[0]->sum + key + c[1]->ml, max(c[0]->ml, c[0]->sum + key));
        mr = max(c[1]->sum + key + c[0]->mr, max(c[1]->mr, c[1]->sum + key));
        ms = max(c[0]->mr + key + c[1]->ml, max(c[0]->ms, c[1]->ms));
        ms = max(max(c[0]->mr + key, c[1]->ml + key), max(key, ms));
        return size = c[0]->size + c[1]->size + 1, this;
    }
}Tnull, *null = &Tnull, buf[MaxNode], *cbuf = buf;

struct splay {
    Node* root;
    void zig(bool d) {
         Node *t = root->c[d]; root->c[d] = null->c[d];
         null->c[d] = root; root = t;
    }
    void zigzig(bool d) {
         Node* t = root->c[d]->c[d]; root->c[d]->c[d] = null->c[d];
         null->c[d] = root->c[d]; root->c[d] = null->c[d]->c[!d];
         null->c[d]->c[!d] = root->rz(); root = t;
    }
    void finish(bool d) {
         Node *t = null->c[d], *p = root->c[!d];
         while (t != null) {
               t = null->c[d]->c[d]; null->c[d]->c[d] = p;
               p = null->c[d]->rz(); null->c[d] = t;
         } root->c[!d] = p;
    }
    void select(int k) {
         for (;;) {
             root->pd(1); bool d = (k > (t = root->c[0]->size));
             if (k == t) break; if (d) k -= (t + 1);
             root->c[d]->pd(1); bool dd = (k > (t = root->c[d]->c[0]->size));
             if (k == t) {zig(d); break;} if (dd) k -= (t + 1);
             d != dd? zig(d), zig(dd): zigzig(d);
         }finish(0); finish(1); root->rz();
    }
    void ins(int x) {
         root->pd(1); Node* oldroot = root;
         root = new(cbuf++)Node(x, root->c[0], root);
         oldroot->c[0] = null; oldroot->rz(); root->rz();
    }
    void Insert(int pos, int x) {select(pos); ins(x);}
    Node* GetSeg(int pos, int tot) {
         select(pos - 2); Node* oldroot = root->pd(1);
         root = root->c[1]->pd(1); select(tot);
         oldroot->c[1] = root; root = oldroot->rz();
         return root->c[1]->c[0];
    }
    void UpdateSeg() {
         root->c[1]->c[0]->pd(1);
         root->c[1]->rz(); root->rz();
    }
    splay() {root = (new(cbuf++)Node(*null))->rz(); Insert(0, -oo);}
}seq;

void Solve() {
     scanf("%s ", o); int pos, tot, x;
     if (o[0] == 'I') {
        scanf("%d%d ", &pos, &tot);
        for (int i = 1; i <= tot; ++i) 
            scanf("%d ", &x), seq.Insert(pos + i, x);
     }
     if (o[0] == 'D') {
        scanf("%d%d ", &pos, &tot); 
        seq.GetSeg(pos + 1, tot); 
        seq.root->c[1]->c[0] = null; seq.UpdateSeg();
     }
     if (o[2] == 'K') {
        scanf("%d%d%d", &pos, &tot, &x);
        Node* t = seq.GetSeg(pos + 1, tot); 
        t->key = t->Same = x; seq.UpdateSeg();         
     }
     if (o[0] == 'R') {
        scanf("%d%d%d", &pos, &tot);
        seq.GetSeg(pos + 1, tot)->rev ^= 1; seq.UpdateSeg();
     }
     if (o[0] == 'G') {
        scanf("%d%d%d", &pos, &tot);
        printf("%d\n", seq.GetSeg(pos + 1, tot)->sum);
     }
     if (o[2] == 'X') printf("%d\n", seq.root->ms);
}

int main() {

    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);

    scanf("%d%d", &N, &M); int x;
    for (int i = 1; i <= N; ++i)
        scanf("%d ", &x), seq.Insert(i, x);
    for (int i = 1; i <= M; ++i) 
        Solve();

    return 0;

}

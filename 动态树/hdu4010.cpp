#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<climits>
#include<algorithm>

using namespace std;

typedef long long LL;

const int Neg = INT_MIN / 3, oo = INT_MAX / 3;
const int MaxNode = 300000 + 5;

#define nonRoot(x) ((x)->fa->c[0] == (x) || (x)->fa->c[1] == (x))
#define nonNull(x) ((x)->c[0] != (x) && (x)->c[1] != (x))

int N, M; char o[20 + 5];
void* stk[MaxNode];

struct Node {
	
	int key, ma, add, rev; Node *fa, *c[2];

	Node(): ma(Neg), add(0), rev(0){
		fa = c[0] = c[1] = this;
	}

	Node(int _key, Node* _fa, Node* _c0, Node* _c1): key(_key), add(0), rev(0) {
		fa = _fa; c[0] = _c0; c[1] = _c1;
	}

	void rz() {
		c[0]->fa = c[1]->fa = this;
		ma = max(key, max(c[0]->ma, c[1]->ma));
	}

	void flip() {
		if (nonNull(this)) {
			swap(c[0], c[1]);
			rev ^= 1;
		}
	}

	void addto(int x) {
		if (nonNull(this)) {
			key += x; ma += x; add += x;
		}
	}

	void pd() {
		if (add) {
			c[0]->addto(add); c[1]->addto(add);
			add = 0;
		}
		if (rev) {
			c[0]->flip(); c[1]->flip();
			rev = 0;
		}
	}

	void zig(bool d) {
		Node *x = fa, *y = x->fa;
		x->c[d] = c[!d]; x->c[d]->fa = c[!d] = x;
		if (y->c[d] == x) y->c[d] = this;
		else if (y->c[!d] == x) y->c[!d] = this;
		fa = y; x->fa = this; x->rz();
	}

	void splay() {
		int top = 0; stk[top++] = this;
		for (Node* v = this; nonRoot(v); v = v->fa) stk[top++] = v->fa;
		for (int i = top - 1; i >= 0; --i) ((Node*)stk[i])->pd(); 
		while (nonRoot(this)) {
			bool d = fa->c[1] == this;
			if (!nonRoot(fa)) {zig(d); break;}
			bool dd = fa->fa->c[1] == fa;
			d != dd? (zig(d), zig(dd)): (fa->zig(dd), zig(d));
		} rz();
	}

}Tnull, *null = &Tnull;

struct LinkCut {

	Node nds[MaxNode]; bool vis[MaxNode]; int que[MaxNode];

	struct etp {
		int t, c; etp* nxt;
		etp() {}
		etp(int _t, etp* _nxt): t(_t), nxt(_nxt) {}
	}*e[MaxNode], buf[MaxNode * 2], *cbuf;
	
	void Me(int a, int b) {
		e[a] = new(cbuf++)etp(b, e[a]);
		e[b] = new(cbuf++)etp(a, e[b]);
	}

	void access(Node* u) {
		for (Node* v = null; u != null; u = u->fa) {
			u->splay(); u->c[1] = v; (v = u)->rz();
		}
	}

	Node* expose(Node* u) {
		access(u); u->splay();
		while (u->c[0] != null) {
			u->pd(); u = u->c[0];
		} u->splay(); return u;
	}

	void setRoot(Node* u) {
		access(u); u->splay(); u->flip();
	}

	void join(Node* u, Node* v) {
		setRoot(u); 
		u->fa = v; access(u);
	}

	void cut(Node* u) {
		access(u); u->splay(); 
		u->c[0]->fa = null; u->c[0] = null; u->rz();
	}

	Node* query(Node* x, Node* y) {
		access(x);
		for (Node *u = y, *v = null; u != null; u = u->fa) {
			if (u->splay(), u->fa == null) return v;	
			u->c[1] = v; (v = u)->rz();
		}
	}

	void modify(Node* u, int x) {
		access(u); u->splay(); u->key = x; u->rz();		
	}

	void bfs(int now) {
		memset(vis, false, sizeof(vis)); int cnt = 0, top = 0;
		que[top++] = now; vis[now] = true;
		while (cnt != top) {
			now = que[cnt];
			for (etp* u = e[now]; u; u = u->nxt) if (!vis[u->t]) {
				que[top++] = u->t; vis[u->t] = true;
				join(nds + u->t, nds + now);
			} cnt++;
		}
	}

	void reset() {
		cbuf = buf; memset(e, 0, sizeof(e));	
	}

}LCT;

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	while (scanf("%d", &N) != -1) {
		LCT.reset();
		int a, b, x, y, w;
		for (int i = 1; i < N; ++i) {
			scanf("%d%d", &a, &b);
			LCT.Me(a, b);	
		}
		for (int i = 1; i <= N; ++i) {
			scanf("%d", &x);
			LCT.nds[i] = Node(x, null, null, null);
			LCT.nds[i].rz();
		}LCT.bfs(1);
		scanf("%d", &M); int tp;
		while (M--) {
			scanf("%d", &tp);
			if (tp == 1) {
				scanf("%d%d", &x, &y);
				if (LCT.expose(LCT.nds + x) == LCT.expose(LCT.nds + y)) puts("-1");
				else {
					LCT.join(LCT.nds + x, LCT.nds + y);
				}
			}
			if (tp == 2) {
				scanf("%d%d", &x, &y);
				if (x == y || LCT.expose(LCT.nds + x) != LCT.expose(LCT.nds + y)) puts("-1");
				else {
					LCT.setRoot(LCT.nds + x);					
					LCT.cut(LCT.nds + y);
				}
			}
			if (tp == 3) {
				scanf("%d%d%d", &w, &x, &y);
				if (LCT.expose(LCT.nds + x) != LCT.expose(LCT.nds + y)) puts("-1");
				else {
					Node *v = LCT.query(LCT.nds + x, LCT.nds + y), *u = v->fa; 
					v->addto(w); u->c[1]->addto(w);
					u->key += w; u->ma += w;
				}
			}
			if (tp == 4) {
				scanf("%d%d", &x, &y);
				if (LCT.expose(LCT.nds + x) != LCT.expose(LCT.nds + y)) puts("-1");
				else {
					Node *v = LCT.query(LCT.nds + x, LCT.nds + y), *u = v->fa;
					printf("%d\n", max(u->key, max(u->c[1]->ma, v->ma)));
				}
			}
		}
		puts("");
	}

	return 0;

}


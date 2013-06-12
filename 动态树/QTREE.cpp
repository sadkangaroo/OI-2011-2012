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

const int Neg = INT_MIN, MaxNode = 10000 + 5, MaxE = MaxNode * 2;

#define nonRoot(x) ((x)->fa->c[0] == (x) || (x)->fa->c[1] == (x))
#define nonNull(x) ((x)->c[0] != (x) && (x)->c[1] != (x))

int T, N, father[MaxNode]; char o[20 + 5];
bool vis[MaxNode];

struct pr {
	int a, b;
	pr() {}
	pr(int _a, int _b): a(_a), b(_b) {}
}es[MaxNode]; int tot;

struct etp {
	int t, c; etp* nxt;
	etp() {};
	etp(int _t, int _c, etp* _nxt): t(_t), c(_c), nxt(_nxt) {}
}*e[MaxNode], buf[MaxE], *cbuf;

void Me(int a, int b, int c) {
	e[a] = new(cbuf++)etp(b, c, e[a]);
	e[b] = new(cbuf++)etp(a, c, e[b]);
}

struct Node {
	
	int key, ma; Node *fa, *c[2];

	Node(): ma(Neg) {
		fa = c[0] = c[1] = this;
	}

	void rz() {
		c[0]->fa = c[1]->fa = this;
		ma = max(key, max(c[0]->ma, c[1]->ma));
	}

	void zig(bool d) {
		Node *x = fa, *y = x->fa;
		x->c[d] = c[!d]; x->c[d]->fa = c[!d] = x;
		if (y->c[d] == x) y->c[d] = this;
		else if (y->c[!d] == x) y->c[!d] = this;
		fa = y; x->fa = this; x->rz();
	}

	void splay() {
		while (nonRoot(this)) {
			bool d = fa->c[1] == this;
			if (!nonRoot(fa)) {zig(d); break;}
			bool dd = fa->fa->c[1] == fa;
			d != dd? (zig(d), zig(dd)): (fa->zig(dd), zig(d));
		} rz();
	}

}Tnull, *null = &Tnull, nds[MaxNode];

void access(Node* u) {
	for (Node* v = null; u != null; u = u->fa) {
		u->splay(); u->c[1] = v; (v = u)->rz();
	}
}

void join(Node* u, Node* v) {
	u->fa = v; access(u);
}

void query(Node* x, Node* y) {
	access(x);
	for (Node *u = y, *v = null; u != null; u = u->fa) {
		if (u->splay(), u->fa == null) {
			printf("%d\n", max(u->c[1]->ma, v->ma));
		} u->c[1] = v; (v = u)->rz();
	}
}

void modify(Node* u, int x) {
	access(u); u->splay(); u->key = x; u->rz();		
}

void dfs(int now) {
	vis[now] = true;
	for (etp* u = e[now]; u; u = u->nxt) if (!vis[u->t]) {
		father[u->t] = now;
		join(nds + u->t, nds + now); modify(nds + u->t, u->c);
		dfs(u->t);
	}	
}

int main() {

	freopen("test.in", "r", stdin);

	scanf("%d ", &T);
	while (T--) {
		memset(e, 0, sizeof(e));
		cbuf = buf; tot = 0;
		scanf("%d ", &N); int a, b, c;
		for (int i = 1; i <= N; ++i) {
			Node* u = nds + i;
			u->fa = u->c[0] = u->c[1] = null;
		}
		for (int i = 1; i < N; ++i) {
			scanf("%d%d%d ", &a, &b, &c);
			es[++tot] = pr(a, b);
			Me(a, b, c);	
		}
		memset(vis, false, sizeof(vis));
		father[1] = 0; dfs(1);
		for (int i = 1; i < N; ++i) 
			if (father[es[i].a] == es[i].b) swap(es[i].a, es[i].b);
		while (scanf("%s ", o) && o[0] != 'D') {
			if (o[0] == 'C') {
				scanf("%d%d ", &a, &b);
				modify(nds + es[a].b, b);
			}
			if (o[0] == 'Q') {
				scanf("%d%d ", &a, &b); 
				query(nds + a, nds + b);	
			}
		}
	}
	
	return 0;

}

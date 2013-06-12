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

const int MaxNode = 30000 + 5;

#define nonRoot(x) ((x)->fa->c[0] == (x) || (x)->fa->c[1] == (x))
#define nonNull(x) ((x)->c[0] != (x) && (x)->c[1] != (x))

int N, M; char o[20 + 5];
void* stk[MaxNode];

struct Node {
	
	int key, s, rev; Node *fa, *c[2];

	Node(): key(0), rev(0), s(0) {
		fa = c[0] = c[1] = this;
	}

	Node(int _key, Node* _fa, Node* _c0, Node* _c1): key(_key), s(_key), rev(0) {
		fa = _fa; c[0] = _c0; c[1] = _c1;
	}

	void rz() {
		c[0]->fa = c[1]->fa = this;
		s = c[0]->s + c[1]->s + key;
	}

	void flip() {
		if (nonNull(this)) {
			swap(c[0], c[1]);
			rev ^= 1;
		}
	}

	void pd() {
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

}Tnull, *null = &Tnull, nds[MaxNode];

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

void join(Node* u, Node* v) {
	if (expose(v) == expose(u)) {puts("no"); return;}
	puts("yes");
	u->splay(); u->flip(); u->fa = v; access(u);
}

void query(Node* x, Node* y) {
	if (expose(y) != expose(x)) {puts("impossible"); return;}
	for (Node *u = y, *v = null; u != null; u = u->fa) {
		if (u->splay(), u->fa == null) {
			printf("%d\n", u->c[1]->s + u->key + v->s);
		} u->c[1] = v; (v = u)->rz();
	}
}

void modify(Node* u, int x) {
	access(u); u->splay(); u->key = x; u->rz();		
}

int main() {

	freopen("test.in", "r", stdin);

	scanf("%d", &N); int x, y;	
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &x); nds[i] = Node(x, null, null, null);
	}
	scanf("%d ", &M);
	while (M--) {
		scanf("%s%d%d ", o, &x, &y);
		if (o[0] == 'b') join(nds + x, nds + y);
		if (o[0] == 'p') modify(nds + x, y);
		if (o[0] == 'e') query(nds + x, nds + y);
	}
	
	return 0;

}

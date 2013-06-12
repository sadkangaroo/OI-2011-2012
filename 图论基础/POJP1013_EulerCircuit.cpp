#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<string>
#include<cctype>
#include<algorithm>
#include<complex>
#include<vector>
#include<queue>
#include<set>
#include<map>

using namespace std;

typedef long long LL;

const int MaxNode = 100000 + 5, MaxE = 1000000 * 2 + 5;

int N, M, D;

struct etp {
	int t, tag; etp *nxt, *p;
	etp() {}
	etp(int _t, int _tag, etp* _nxt): t(_t), tag(_tag), nxt(_nxt) {}
	void* operator new(size_t, void* p) {return p;}
}*e[MaxNode], buf[MaxE], *cbuf = buf; 

struct edge {
	int fro; etp* u;
	edge() {}
	edge(int _fro, etp* _u): fro(_fro), u(_u) {}
}ans[MaxE]; int num;

void Me(int a, int b, int tab, int tba) {
	e[a] = new(cbuf++)etp(b, tab, e[a]);
	e[b] = new(cbuf++)etp(a, tba, e[b]);
	(cbuf - 1)->p = cbuf - 2; (cbuf - 2)->p = cbuf - 1;
}

etp* Stack[MaxE]; int Cnt[MaxE];

void dfs(int now) {
	int top = 0; Stack[0] = e[now]; Cnt[0] = now;
	while (true) {
		if (Stack[top]) {
			if (Stack[top]->tag == 0) {
				Stack[top]->tag = Stack[top]->p->tag = 1;
				Stack[top + 1] = e[Stack[top]->t];
				top++; Cnt[top] = Stack[top - 1]->t;
			} else Stack[top] = Stack[top]->nxt;
		}
		else {
			top--; if (top < 0) break;
			ans[num++] = edge(Cnt[top], Stack[top]);
			Stack[top] = Stack[top]->nxt;
		}
	}
	/*
	for (etp* u = e[now]; u; u = u->nxt) if (u->tag == 0) {
		u->tag = u->p->tag = 1;
		dfs(u->t);
		ans[num++] = edge(now, u);
	}
	*/
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	scanf("%d%d", &N, &M); int a, b;
	memset(e, 0, sizeof(e));
	for (int i = 1; i <= M; ++i) {
		scanf("%d%d", &a, &b);
		Me(a, b, 0, 0);
	}
	D = M * 2 / N;
	while (D != 1) {
		num = 0; 
		for (int i = 1; i <= N; ++i) dfs(i);
		for (int i = 0; i < num; ++i)
			if (i & 1) ans[i].u->tag = ans[i].u->p->tag = -1;
		for (int i = 1; i <= N; ++i)
			for (etp* u = e[i]; u; u = u->nxt)
				if (u->tag == 1) u->tag = 0;
		D >>= 1;
	}
	for (int i = 0; i < num; ++i)
		if (ans[i].u->tag != -1)
			printf("%d %d\n", ans[i].fro, ans[i].u->t);

	return 0;

}


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

#define lc (now * 2)
#define rc (now * 2 + 1)

typedef long long LL;

const int MaxN = 1000000 + 5;

int N, M;

struct Node {
	int a4, a7, a47, a74, rev;
	Node(): a4(0), a7(0), a47(0), a74(0), rev(0) {}
}st[MaxN * 4];

inline void rz(int now) {
	st[now].a4 = st[lc].a4 + st[rc].a4;
	st[now].a7 = st[lc].a7 + st[rc].a7;
	st[now].a47 = max(st[lc].a47 + st[rc].a7, st[lc].a4 + st[rc].a47);
	st[now].a74 = max(st[lc].a74 + st[rc].a4, st[lc].a7 + st[rc].a74);
}

void ins(int now, int l, int r, int p, int x) {
	if (l == r) {
		if (x == 4) st[now].a4 = 1; else st[now].a7 = 1;
		st[now].a47 = st[now].a74 = 1;
		return;
	}
	int mid = (l + r) / 2;
	if (p <= mid) ins(lc, l, mid, p, x); 
	else ins(rc, mid + 1, r, p, x);
	rz(now);
}

void flip(int now) {
	st[now].rev ^= 1;
	swap(st[now].a4, st[now].a7);
	swap(st[now].a47, st[now].a74);
}

void pd(int now) {
	st[now].rev = 0;
	flip(lc); flip(rc);
}

void rev(int now, int l, int r, int a, int b) {
	if (a <= l && b >= r) {
		flip(now);
		return;
	}
	if (st[now].rev) pd(now);
	int mid = (l + r) / 2;
	if (a <= mid) rev(lc, l, mid, a, b);
	if (b >= mid + 1) rev(rc, mid + 1, r, a, b);
	rz(now);
}

char o[100 + 5];

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	scanf("%d%d ", &N, &M);
	for (int i = 1; i <= N; ++i) {
		ins(1, 1, N, i, getchar() - '0');
	} getchar();
	while (M--) {
		scanf("%s ", o);
		if (o[0] == 'c') printf("%d\n", st[1].a47);
		else {
			int a, b;
			scanf("%d%d ", &a, &b);
			rev(1, 1, N, a, b);
		}
	}

	return 0;

}


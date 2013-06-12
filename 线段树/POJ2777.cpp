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

#define lc (now * 2)
#define rc (now * 2 + 1)

const int MaxN = 100000 + 5, MaxCol = 30 + 5;

int N, C, M;
int st[MaxN * 4], single[MaxN * 4], col;

void paintSingle(int now, int c) {
	single[now] = c;
	st[now] = (1 << c);
}

void rz(int now) {
	st[now] = (st[lc] | st[rc]);
}

void pd(int now) {
	paintSingle(lc, single[now]); paintSingle(rc, single[now]);
	single[now] = -1;
}

void paint(int now, int l, int r, int a, int b, int c) {
	if (a <= l && b >= r) {
		paintSingle(now, c);
		return;
	}
	if (single[now] != -1) pd(now);
	int mid = (l + r) / 2;
	if (a <= mid) paint(lc, l, mid, a, b, c);
	if (b >= mid + 1) paint(rc, mid + 1, r, a, b, c);
	rz(now);
}

void query(int now, int l, int r, int a, int b) {
	if (a <= l && b >= r) {
		col |= st[now];
		return;
	}
	if (single[now] != -1) pd(now);
	int mid = (l + r) / 2;
	if (a <= mid) query(lc, l, mid, a, b);
	if (b >= mid + 1) query(rc, mid + 1, r, a, b);
	rz(now);
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	scanf("%d%d%d ", &N, &C, &M);
	paint(1, 1, N, 1, N, 0);
	while (M--) {
		int a, b, c;
		if (getchar() == 'C') {
			scanf("%d%d%d ", &a, &b, &c); c--;
			if (a > b) swap(a, b);
			paint(1, 1, N, a, b, c);
		}
		else {
			scanf("%d%d ", &a, &b);
			if (a > b) swap(a, b);
			col = 0;
			query(1, 1, N, a, b);
			int ans = 0;
			for (int i = 0; i < C; ++i) if (col & (1 << i)) ans++;
			printf("%d\n", ans);
		}
	}

	return 0;

}


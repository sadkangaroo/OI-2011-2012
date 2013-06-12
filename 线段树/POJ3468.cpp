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

const int MaxN = 100000 + 5;

int N, Q;
LL cnt;
struct Node {
	LL sum, add;
	Node(): sum(0), add(0) {}
}st[MaxN * 4];

void rz(int now) {
	st[now].sum = st[lc].sum + st[rc].sum;
}

void addSum(int now, int l, int r, int x) {
	st[now].sum += (LL)(r - l + 1) * x;
	st[now].add += x;
}

void pd(int now, int l, int r) {
	int mid = (l + r) / 2;
	addSum(lc, l, mid, st[now].add); addSum(rc, mid + 1, r, st[now].add);
	st[now].add = 0;
}

void add(int now, int l, int r, int a, int b, int x) {
	if (a <= l && b >= r) {
		addSum(now, l, r, x);
		return;
	}
	if (st[now].add) pd(now, l, r);
	int mid = (l + r) / 2;
	if (a <= mid) add(lc, l, mid, a, b, x);
	if (b >= mid + 1) add(rc, mid + 1, r, a, b, x);
	rz(now);
}

void query(int now, int l, int r, int a, int b) {
	if (a <= l && b >= r) {
		cnt += st[now].sum;
		return;
	}
	if (st[now].add) pd(now, l, r);
	int mid = (l + r) / 2;
	if (a <= mid) query(lc, l, mid, a, b);
	if (b >= mid + 1) query(rc, mid + 1, r, a, b);
	rz(now);
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	scanf("%d%d", &N, &Q); int x;
	for (int i = 1; i <= N; ++i) {
		scanf("%d ", &x);
		add(1, 1, N, i, i, x);
	}
	while (Q--) {
		int a, b, c;
		if (getchar() == 'Q') {
			scanf("%d%d ", &a, &b);
			cnt = 0;
			query(1, 1, N, a, b);
			cout << cnt << endl;
		}
		else {
			scanf("%d%d%d ", &a, &b, &c);
			add(1, 1, N, a, b, c);
		}
	}

	return 0;

}


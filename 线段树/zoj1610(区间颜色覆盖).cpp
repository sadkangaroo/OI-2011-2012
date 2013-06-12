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

const int MaxLen = 8000 + 5, MaxCol = 8000 + 5;

int st[MaxLen * 4];
int col[MaxLen], ans[MaxCol + 5];

int N;

void paint(int now, int l, int r, int a, int b, int c) {
	if (a <= l && b >= r) {
		st[now] = c;
		return;
	}
	if (st[now] != -1) {
		st[lc] = st[rc] = st[now];
		st[now] = -1;
	}
	int mid = (l + r) / 2;
	if (a <= mid) paint(lc, l, mid, a, b, c);
	if (b >= mid + 1) paint(rc, mid + 1, r, a, b, c);
}

void query(int now, int l, int r, int p) {
	if (st[now] != -1) {
		col[p] = st[now];
		return;
	}
	if (l == r) return;
	int mid = (l + r) / 2;
	if (p <= mid) query(lc, l, mid, p);
	else query(rc, mid + 1, r, p);
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	while (scanf("%d", &N) != -1) {
		int a, b, c;
		paint(1, 0, MaxLen - 1, 0, MaxLen - 1, MaxCol + 1);
		while (N--) {
			scanf("%d%d%d", &a, &b, &c);
			b--;
			if (a <= b) paint(1, 0, MaxLen - 1, a, b, c);
		}
		for (int i = 0; i < MaxLen; ++i) query(1, 0, MaxLen - 1, i);
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i < MaxLen; ++i) if (col[i] != col[i - 1])
			ans[col[i - 1]]++;
		ans[col[MaxLen - 1]]++;
		for (int i = 0; i <= MaxCol; ++i) if (ans[i])
			printf("%d %d\n", i, ans[i]);
		puts("");
	}

	return 0;

}


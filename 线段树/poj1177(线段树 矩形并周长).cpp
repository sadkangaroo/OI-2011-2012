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

const int MaxM = 5000 + 5;

struct Line {
	int y1, y2, x, t;
	Line() {}
	Line(int _y1, int _y2, int _x, int _t): y1(_y1), y2(_y2), x(_x), t(_t) {}
	bool operator < (const Line &tt)const {
		if (x == tt.x) return t > tt.t;
		return x < tt.x;
	}
}Ln[MaxM * 2];

struct Node {
	int	sum, cover, num, lx, rx;
	Node(): sum(0), cover(0), num(0), lx(0), rx(0) {}
}st[MaxM * 2 * 4];

int M, N, ys[MaxM * 2];

void rz(int now) {
	if (st[now].cover) return;
	st[now].sum = st[lc].sum + st[rc].sum;
	st[now].lx = st[lc].lx; st[now].rx = st[rc].rx;
	if (st[lc].rx && st[rc].lx) st[now].num = st[lc].num + st[rc].num - 1;
	else st[now].num = st[lc].num + st[rc].num;
}

void ins(int now, int l, int r, Line &ln) {
	if (ln.y1 <= ys[l] && ln.y2 >= ys[r]) {
		st[now].cover += ln.t;
		if (st[now].cover) {
			st[now].sum = ys[r] - ys[l];
			st[now].num = st[now].lx = st[now].rx = 1;
		}
		else {
			if (r - l == 1) {st[now].sum = st[now].num = st[now].lx = st[now].rx = 0;}
			else rz(now);
		}
		return;
	}	
	int mid = (l + r) / 2;
	if (ln.y1 < ys[mid]) ins(lc, l, mid, ln);
	if (ln.y2 > ys[mid]) ins(rc, mid, r, ln);
	rz(now);
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	scanf("%d", &M);
	int x1, y1, x2, y2;
	for (int i = 0; i < M; ++i) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		Ln[i * 2] = Line(y1, y2, x1, 1);
		Ln[i * 2 + 1] = Line(y1, y2, x2, -1);
		ys[i * 2] = y1; ys[i * 2 + 1] = y2;
	}
	M *= 2; N = 0;
	sort(ys, ys + M);
	sort(Ln, Ln + M);
	for (int i = 0; i < M; ++i) if (i == 0 || ys[i] != ys[i - 1])
		ys[N++] = ys[i];
	int last = 0, ans = 0;
	for (int i = 0; i < M; ++i) {
		ins(1, 0, N - 1, Ln[i]);	
		ans += abs(last - st[1].sum);
		if (i != M - 1) ans += st[1].num * 2 * (Ln[i + 1].x - Ln[i].x);
		last = st[1].sum;
	}
	printf("%d\n", ans);
	return 0;

}


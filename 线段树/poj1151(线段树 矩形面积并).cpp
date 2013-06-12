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

const int MaxN = 100 + 5;
const double eps = 1e-7;

#define ge(x, y) ((x) - (y) > -eps)
#define le(x, y) ((y) - (x) > -eps)
#define eq(x, y) (ge(x, y) && le(x, y))
#define lc (now * 2)
#define rc (now * 2 + 1)

int N, cover[MaxN * 2 * 4];
double ys[MaxN * 2], sum[MaxN * 2 * 4];

struct _Line{
	double y1, y2, x;
	int t;
	_Line() {}
	_Line(double _y1, double _y2, double _x, int _t): y1(_y1), y2(_y2), x(_x), t(_t) {}
	bool operator < (const _Line &tt)const {
		if (eq(x, tt.x)) return t < tt.t;
		return x < tt.x;
	}
}Line[MaxN * 2];

void ins(int now, int l, int r, _Line &ln) {
	if (le(ln.y1, ys[l]) && ge(ln.y2, ys[r])) {
		cover[now] += ln.t;
		if (cover[now]) sum[now] = ys[r] - ys[l];
		else sum[now] = (r - l == 1? 0: sum[lc] + sum[rc]);
		return;
	}
	if (r - l == 1) return;
	int mid = (l + r) / 2;
	if (ln.y1 < ys[mid] - eps) ins(lc, l, mid, ln);
	if (ln.y2 > ys[mid] + eps) ins(rc, mid, r, ln);
	if (cover[now] == 0) sum[now] = sum[lc] + sum[rc];
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	int te = 0;
	while (scanf("%d", &N) && N) {
		double x1, y1, x2, y2;
		for (int i = 0; i < N; ++i) {
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			Line[i * 2] = _Line(y1, y2, x1, 1);
			Line[i * 2 + 1] = _Line(y1, y2, x2, -1);
			ys[i * 2] = y1; ys[i * 2 + 1] = y2;
		}
		N = N * 2;
		sort(ys, ys + N);
		sort(Line, Line + N);
		double ans = 0;
		for (int i = 0; i < MaxN * 2 * 4; ++i) {sum[i] = 0; cover[i] = 0;}
		for (int i = 0; i < N; ++i) {
			ins(1, 0, N - 1, Line[i]);
			if (i != N - 1) ans += (Line[i + 1].x - Line[i].x) * sum[1];
		}
		printf("Test case #%d\n", ++te);
		printf("Total explored area: %.2lf\n", ans);
		puts("");
	}

	return 0;

}


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

const int MaxN = 8000 + 5, MaxM = 8000 + 5, MaxC = 8000 + 5;

int N, M, C;
int a[MaxM], b[MaxM], c[MaxM];
int col[MaxN], fa[MaxN], ans[MaxC];

int grand(int x) {
	if (fa[x] == x) return x;
	return fa[x] = grand(fa[x]);
}

void paint(int a, int b, int c) {
	while (a <= b) {
		if (col[b] == -1) {
			col[b] = c;
			b--;
		}
		else b = grand(b) - 1; 
	}
}

void uni(int a, int b) {
	if (col[b + 1] != -1 && grand(b + 1) != grand(b)) 
		fa[b + 1] = grand(b);
	while (b >= a) {
		int t2 = grand(b);
		if (t2 == 0 || t2 < a) break;
		if (col[t2 - 1] != -1) 
			fa[t2] = grand(t2 - 1);
		b = t2 - 1;
	}
}

int main() {

	freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);

	while (scanf("%d", &M) != -1) {
		N =	8000; C = 8000; 
		memset(col, -1, sizeof(col));
		for (int i = 0; i <= N; ++i) fa[i] = i;
		for (int i = 1; i <= M; ++i) 
			scanf("%d%d%d", a + i, b + i, c + i);
		for (int i = M; i >= 1; --i) {
			paint(a[i], b[i] - 1, c[i]);
			uni(a[i], b[i] - 1);
		}
		col[N + 1] = C + 1;
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= N + 1; ++i) if (col[i] != col[i - 1])
			if (col[i - 1] != -1) ans[col[i - 1]]++;
		for (int i = 0; i <= C; ++i) if (ans[i]) 
			printf("%d %d\n", i, ans[i]);
		puts("");
	}

	return 0;

}


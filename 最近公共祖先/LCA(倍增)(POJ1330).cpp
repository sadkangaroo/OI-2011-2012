/*
LCA ������ʵ�� �����㷨 Ԥ����NlogN ѯ��logN
Ԥ����ʱ���������ϵ�ÿ���ڵ�p ����f[p][k] ��ʾp�ڵ����ϵ�2^k��Ľڵ㣨NlogN��
ѯ�ʽڵ�a��b�������������ʱ����ͨ�������Ʒֽ⽫�ϵ͵�һ������abs��depth[a]-depth[b])��
��ͨ���������a��b������������ȣ�logN��
code source��POJ 1330 Nearest Common Ancestors
*/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<int> :: iterator vit;
const int Max_N = 10005, Max_K = 15;

int N, T, a, b, root;
int f[Max_N][Max_K], hash[Max_N], depth[Max_N];
vector<int> g[Max_N];

void initial() {
    scanf("%d", &N);
    memset(f, 0, sizeof(f));
    memset(hash, 0, sizeof(hash));
    for (int i = 1; i <= N; ++i) g[i].clear();
    for (int i = 1; i < N; ++i) {
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        hash[b]++;
    }
    for (int i = 1; i <= N; ++i)
        if (!hash[i]) {
            root = i;
            break;
        }
    depth[root] = 0;
}

void dfs(int p) {
    for (int i = 1; i < Max_K; ++i)
        f[p][i]=f[f[p][i - 1]][i - 1];
    for (vit iter = g[p].begin(); iter != g[p].end(); ++iter) {
        depth[*iter]=depth[p] + 1;
        f[*iter][0]=p;
        dfs(*iter);
    } 
}

int main() {

    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout); 

    scanf("%d", &T);
    while (T--) {
        initial();
        dfs(root);    
    }

    return (0-0);

}

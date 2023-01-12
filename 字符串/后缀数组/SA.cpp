const int N = 101000;
char s[N];
int sa[N], rk[N], ht[N], n;
// 0-based sa 表示第i大的为哪个，rk 表示第i个后缀第几大
// ht表示 lcp(sa[i], sa[i-1])
void buildSA(char *s, int *sa, int *rk, int *ht, int n, int m = 128) {
	static int x[N], y[N], c[N];
	s[n] = 0;
	for (int i = 0; i < m; i++) c[i] = 0;
	for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (int i = 1; i < m; i++) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
	for (int k = 1; k < n; k <<= 1) {
		int p=0;
		for (int i = n - 1; i >= n - k; i--) y[p++] = i;
		for (int i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
		for (int i = 0; i < m; i++) c[i] = 0;
		for (int i = 0; i < n; i++) c[x[y[i]]]++;
		for (int i = 1; i < m; i++) c[i] += c[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1; x[sa[0]] = 0; y[n] = -1;
		for (int i = 1; i < n; i++) {
			if (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k])
				x[sa[i]] = p - 1;
			else
				x[sa[i]] = p++;
		}
		if (p == n) break;
		m = p;
	}
	for (int i = 0; i < n; i++) rk[sa[i]] = i;
	int k = 0;
	for (int i = 0; i < n; i++) {
		k = max(k - 1, 0);
		if (rk[i] == 0) continue;
		int j = sa[rk[i] - 1];
		while (s[i + k] == s[j + k]) k++;
		ht[rk[i]] = k;
	}
}

int LCP(int u, int v) {
	if (u == v) return n - u;
	if (rk[u] > rk[v]) swap(u, v);
	// RMQ(ht, rk[u] + 1, rk[v])
}

int main() {
	scanf("%s", s);
	n = strlen(s);
	buildSA(s, sa, rk, ht, n);
	for (int i = 0; i < n; i++) printf("%d ", sa[i] + 1); puts("");
	for (int i = 1; i < n; i++) printf("%d ", ht[i]); puts("");
}
/*
给定一个长度为 n 的字符串 S，令 Ti 表示它从第 i 个字符开始的后缀。
求∑(1≤i<j≤n)len(Ti)+len(Tj)−2×lcp(Ti,Tj)
其中，len(a) 表示字符串 a 的长度，lcp(a,b) 表示字符串 a 和字符串 b 的最长公共前缀。
*/

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

int stk[N],l[N],r[N];
ll ans=0;

void dfs(int u,int L,int R){//u表示数组的第几个元素
	ans-=2LL*ht[u]*(u-L+1)*(R-u+1);
	if(l[u]) dfs(l[u],L,u-1);
	if(r[u]) dfs(r[u],u+1,R);
}

void build(){
    int top=0;
    //for(int i=1;i<=n;++i) l[i]=r[i]=0;
    for(int i=1;i<n;++i){
        int k=top;
        while(k>0&&ht[stk[k-1]]>ht[i]) --k;
        if(k) r[stk[k-1]]=i;
        if(k<top) l[i]=stk[k];
        stk[k++]=i;
        top=k;
    }
	dfs(stk[0],1,n-1);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%s", s);
	n = strlen(s);
	buildSA(s, sa, rk, ht, n);
	ans=(ll)(n-1)*n*(n+1)/2;
	build();
	printf("%lld\n",ans);
	return 0;
}
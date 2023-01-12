/*
对于一个给定长度为 n 的字符串，求它的第 k 小子串是什么。

输入格式
第一行是一个仅由小写英文字母构成的字符串 S(|S|≤5×105)。

第二行为两个整数 T(0≤T<2) 和 k(1≤k≤109)。

T=0 则表示不同位置的相同子串算作一个。

T=1 则表示不同位置的相同子串算作多个。

输出格式
输出仅一行，为一个字符串，为第 k 小的子串。如果子串数目不足 k 个，则输出−1。
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

struct DSU {
    vector<int> fa, sz;
	int n;
    DSU(int n) : fa(n+1), sz(n+1, 1),n(n){ 
		for(int i=0 ; i<=n ; ++i) fa[i] = i;
    }
    int find(int x) {
        /*while (x != fa[x]) x = fa[x] = fa[fa[x]];
        return x;*/
        return fa[x]==x?x:fa[x]=find(fa[x]);
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        sz[x] += sz[y];
        fa[y] = x;
        return true;
    }
    int size(int x) { return sz[find(x)]; }
	int size(){
		set<int> st; 
		for(int i=1;i<=n;++i){
			st.insert(find(i));
		}
		return st.size();
	}
};

vector<array<int,3>> ans[N];//对后缀数组每个串,从长度l开始,到长度r结束,每个串都出现了sz次
VI e[N];
int len[N];

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%s", s);
	n = strlen(s);
	buildSA(s, sa, rk, ht, n);
	int T,k;
	scanf("%d%d",&T,&k);
	if(T==0){
		rep(i,0,n){
			if(!i)
				ans[i].pb({1,n-sa[i],1});
			else 
				ans[i].pb({ht[i]+1,n-sa[i],1});
		}
	}else{
		rep(i,1,n){
			e[ht[i]].pb(i);
		}
		rep(i,0,n) len[i]=n-sa[i];
		DSU d(n);
		per(i,0,1+n){
			for(auto u:e[i]){
				u=d.find(u);
				int v=d.find(u-1);
				if(len[u]!=i) ans[u].pb({i+1,len[u],d.size(u)});
				if(len[v]!=i) ans[v].pb({i+1,len[v],d.size(v)});
				d.merge(v,u);
				len[v]=i;
			}
		}
		if(len[0]>0){
			ans[0].pb({1,len[0],n});
		}
		rep(i,0,n) reverse(all(ans[i]));
	}
	rep(i,0,n){
		for(auto [l,r,sz]:ans[i]){
			if(k>(ll)sz*(r-l+1)){
				k-=(ll)sz*(r-l+1);
			}else{
				while((ll)sz*(r-l+1)>=k) r--;
				r++;
				rep(j,sa[i],sa[i]+r) printf("%c",s[j]);
				return 0;
			}
		}
	}
	printf("-1\n");
	return 0;
}
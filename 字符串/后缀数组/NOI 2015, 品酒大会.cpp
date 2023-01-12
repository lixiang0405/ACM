/*
在大会的晚餐上，调酒师 Rainbow 调制了 n 杯鸡尾酒。
这 n 杯鸡尾酒排成一行，其中第 i 杯酒 (1≤i≤n) 被贴上了一个标签 si ，
每个标签都是 26 个小写英文字母之一。
设 str(l,r) 表示第 l 杯酒到第 r 杯酒的 r−l+1 个标签顺次连接构成的字符串。
若 str(p,p0)=str(q,q0)，其中 1≤p≤p0≤n, 1≤q≤q0≤n, p≠q，p0−p+1=q0−q+1=r，
则称第 p 杯酒与第 q 杯酒是“ r 相似” 的。
当然两杯“ r 相似”(r>1)的酒同时也是“ 1 相似”、“ 2 相似”、……、“ (r−1) 相似”的。
特别地，对于任意的 1≤p,q≤n,p≠q，第 p 杯酒和第 q 杯酒都是“ 0 相似”的。
在品尝环节上，品酒师 Freda 轻松地评定了每一杯酒的美味度，
凭借其专业的水准和经验成功夺取了“首席品酒家”的称号，其中第 i 杯酒 (1≤i≤n) 的美味度为 ai 。
现在 Rainbow 公布了挑战环节的问题：
本次大会调制的鸡尾酒有一个特点，如果把第 p 杯酒与第 q 杯酒调兑在一起，
将得到一杯美味度为 ap×aq 的酒。现在请各位品酒师分别对于 r=0,1,2,⋯,n−1 ，
统计出有多少种方法可以选出 2 杯“ r 相似”的酒，
并回答选择 2 杯“r 相似”的酒调兑可以得到的美味度的最大值。
*/

char s[N];
int sa[N], rk[N], ht[N], n,a[N];
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
	vector<ll> maxx,minn,p;
	int n;
    DSU(int n) : fa(n+1), sz(n+1, 1),maxx(n+1),minn(n+1),p(n+1),n(n){ 
		for(int i=0 ; i<n ; ++i) fa[i] = i,maxx[i]=a[sa[i]],minn[i]=a[sa[i]],p[i]=-1e18;
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
		p[x]=max({p[x],maxx[x]*maxx[y],minn[x]*minn[y],maxx[x]*minn[y],minn[x]*maxx[y]});
		maxx[x]=max(maxx[x],maxx[y]);
		minn[x]=min(minn[x],minn[y]);
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

vector<pair<ll,ll>> ans;
VI e[N]; 

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

ll binom(ll n){
	return n*(n-1)/2;
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	scanf("%s",s);
	rep(i,0,n) scanf("%d",&a[i]);
	buildSA(s,sa,rk,ht,n);
	rep(i,1,n) e[ht[i]].pb(i);
	ll res=0,p=-1e18;
	DSU d(n);
	per(i,0,n){
		for(auto u:e[i]){
			int v=d.find(u-1);
			res-=binom(d.size(u))+binom(d.size(v));
			d.merge(v,u);
			res+=binom(d.size(v));
			p=max(p,d.p[v]);
		}
		if(!res)
			ans.pb({res,0});
		else ans.pb({res,p});
	}
	reverse(all(ans));
	for(auto [x,y]:ans){
		cout<<x<<" "<<y<<'\n';
	}
	return 0;
}
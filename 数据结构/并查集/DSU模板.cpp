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
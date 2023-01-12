struct DSU{
    int fa[N];
    int sz[N];
    vector<pair<int&, int>>his_sz;
    vector<pair<int&, int>>his_fa;
    
    void init(int n) {
        for (int i = 1; i <= n; i++)fa[i] = i, sz[i] = 1;
    }
    int find(int x) {
        while (x != fa[x])x = fa[x];
        return x;
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    void merge(int u, int v) {
        int x = find(u);
        int y = find(v);
        if (x == y) return;
        if (sz[x] < sz[y]) std::swap(x, y);
        his_sz.push_back({ sz[x], sz[x] });
        sz[x] = sz[x] + sz[y];
        his_fa.push_back({ fa[y],fa[y] });
        fa[y] = x;
    }
 
    int history() {
        return his_fa.size();
    }
 
    void roll(int h) {
        while (his_fa.size() > h) {
            his_fa.back().first = his_fa.back().second;
            his_fa.pop_back();
            his_sz.back().first = his_sz.back().second;
            his_sz.pop_back();
        }
    }
    
}dsu;
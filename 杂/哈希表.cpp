struct Hash_table{
    static const int V=1000003;
    int fst[V],nxt[V],ptm[V];
    int ctm,T;
    int val[V];
    ll key[V];

    void init(){
        T=0;
        ctm++;
    }

    void insert(ll s,int v){
        int S=s%V;
        if(ptm[S]!=ctm) ptm[S]=ctm,fst[S]=-1;
        for(int j=fst[S];j!=-1;j=nxt[j])
            if(key[j]==s) return;
        nxt[T]=fst[S];
        fst[S]=T;
        key[T]=s;
        val[T]=v;
        T++;
    }

    int query(ll s){
        int S=s%V;
        if(ptm[S]!=ctm) return -1;
        for(int j=fst[S];j!=-1;j=nxt[j])
            if(key[j]==s) return val[j];
        return -1;
    }
}hs;

inline ull splitmix64(ull x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}
constexpr int BIT_MASK(int t) { return t ? BIT_MASK(t >> 1) << 1 | 1 : 0; }
template <typename T, const int BIT, const int LIM>
struct hashTable {
#define idx(key) splitmix64(key) & BIT
    struct {
        int next;
        ull key;
        T val;
    } data[LIM];
    int first[BIT + 1], cnt = 0;
    int find(ull key) {
        for (int i = first[idx(key)]; i; i = data[i].next)
            if (data[i].key == key) return i;
        return 0;
    }
    T& at(int pos) { return data[pos].val; }
    T& operator[](ull key) {
        int pos = find(key);
        if (pos) return at(pos);
        ull K = idx(key);
        data[++cnt] = {first[K], key, T()};
        return at(first[K] = cnt);
    }
    void clear() {
        for (int& i = cnt; i; --i) first[idx(data[i].key)] = 0;
    }
    #undef idx
};
hashTable<int, BIT_MASK(N), BIT_MASK(N)> hash;
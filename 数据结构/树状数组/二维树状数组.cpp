#define lowbit(x) x&(-x)
template<class T>
struct BIT{
    T c[N][N];
    int n,m;
    void resize(int s,int x){n=s,m=x;}

    T query(int x,int y){
        assert(x<=n);
        assert(y<=m);
        T s=0;
        for(int i=x;i;i-=lowbit(i)){
            for(int j=y;j;j-=lowbit(j))
            s+=c[i][j];
        }
        return s;
    }

    void modify(int x,int y,T s){
        assert(x!=0);
        assert(y!=0);
        for(int i=x;i<=n;i+=lowbit(i)){
            for(int j=y;j<=m;j+=lowbit(j))
            c[i][j]+=s;
        }
    }
};
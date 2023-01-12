/*给一棵n个点的树，每个点有点权wi，1号点为根。给q个操作：

1 x y，将x点的点权改成y。

2 x，询问x点子树的点权和，到根的路径的点权和（都包含x这个点）。*/

template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){n=s;}

    T query(int x){
        assert(x<=n);
        T s=0;
        for(;x;x-=lowbit(x)){
            s+=c[x];
        }
        return s;
    }

    void modify(int x,T s){
        assert(x!=0);
        for(;x<=n;x+=lowbit(x)){
            c[x]+=s;
        }
    }
 
    //树状数组上二分
    int ask(T s){
        int pos=0;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos+(1<<i)<=n&&c[pos+(1<<i)]<=s){
                pos+=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};

BIT<ll> c1,c2;
int n,q,l[N],r[N],tot=0,a[N];
vector<int> e[N];

void dfs(int u,int f){
    l[u]=++tot;
    for(auto v:e[u]){
        if(v==f) continue;
        dfs(v,u);
    }
    r[u]=tot;
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&q);
	c1.resize(n);
    c2.resize(n);
    for(int i=0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        c1.modify(l[i],a[i]);
        c2.modify(l[i],a[i]);
        c2.modify(r[i]+1,-a[i]);
    }
    for(int i=0;i<q;++i){
        int ty,x;
        scanf("%d%d",&ty,&x);
        if(ty==1){
            int y;
            scanf("%d",&y);
            int d=y-a[x];
            a[x]=y;
            c1.modify(l[x],d);
            c2.modify(l[x],d);
            c2.modify(r[x]+1,-d);
        }else{
            printf("%lld %lld\n",c1.query(r[x])-c1.query(l[x]-1),c2.query(l[x]));
        }
    }
    return 0;
}

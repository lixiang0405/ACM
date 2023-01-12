/*给一棵n个点的树，每个点有点权wi，1号点为根。给q个操作：

1 x y，将x点的点权改成y。

2 x，询问x点子树的点权和。

3 x，将根换到x位置。*/

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

BIT<ll> c1;
int n,q,l[N],r[N],a[N],tot=0;
vector<int> e[N];
vector<pair<int,int>> son[N];

void dfs(int u,int f){
    l[u]=++tot;
    for(auto v:e[u]){
        if(v==f) continue;
        dfs(v,u);
        son[u].push_back({l[v],r[v]});
    }
    r[u]=tot;
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&q);
	c1.resize(n);
    for(int i=0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    int root=1;
    dfs(1,0);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        c1.modify(l[i],a[i]);
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
        }else if(ty==3){
            root=x;
        }else{
            if(x==root){
                printf("%lld\n",c1.query(n));
            }
            else if(l[x]<l[root]&&r[x]>=r[root]){
                auto it=*prev(upper_bound(son[x].begin(),son[x].end(),pair<int,int>{l[root],r[root]}));
                printf("%lld\n",c1.query(n)-(c1.query(it.second)-c1.query(it.first-1)));
            }else{
                printf("%lld\n",c1.query(r[x])-c1.query(l[x]-1));
            }
        }
    }
    return 0;
}

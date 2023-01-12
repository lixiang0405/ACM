/*给你一棵树，以编号为 1 的节点为根；

回答 m 组询问，每组询问有两个数 x,y(x≠y), 你需要求出 x,y 的最近公共祖先。*/

//公共祖先一定在下，y最早出现的位置之间
unsigned int A, B, C;
inline unsigned int rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}

int n,m,depth[N],p[N],tot=0;
vector<int> e[N];
pair<int,int> ol[LOGN+2][2*N];
ll ans=0;

void dfs(int u,int f){
    p[u]=++tot;
    depth[u]=depth[f]+1;
    ol[0][tot]={depth[u],u};
    for(auto v:e[u]){
        if(v==f) continue;
        dfs(v,u);
        ol[0][++tot]={depth[u],u};
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d%u%u%u", &n, &m, &A, &B, &C);
    for(int i=0;i<n-1;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1,0);
    for(int i=1;i<=LOGN;++i){
        for(int j=1;j+(1<<i)<=tot;++j){
            ol[i][j]=min(ol[i-1][j],ol[i-1][j+(1<<(i-1))]);
        }
    }
    for (int i = 1; i <= m; i++) {
        unsigned int u = rng61() % n + 1, v = rng61() % n + 1;
        int l=p[u],r=p[v];
        if(l>r) swap(l,r);
        int len=31-__builtin_clz(r-l+1);//l=r len=0 l=0 r-(1<<len)+1=l=r
        int d=min(ol[len][l],ol[len][r-(1<<len)+1]).second;
        ans^=1ll*d*i;
    }
    printf("%lld",ans);
    return 0;
}


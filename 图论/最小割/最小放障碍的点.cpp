/*
给定一张 n 个点 m 条边的连通无向图，要求在某些点（不能为 1 号点或者 n 号点）设立障碍，

在 i 号点建立障碍的费用为 ci，要使得 1 号点和 n 号点不连通，求最小花费的方案。
*/

const int V=20005;//节点个数
const int E=201000;//边个数
template<typename T>
struct FlowGraph{
    int s,t,vtot;
    int head[V],etot;
    int dis[V],cur[V];
    struct edge{
        int v,nxt;
        T f;
    }e[E*2];

    void add(int u,int v,T f,T f2=0){
        e[etot]={v,head[u],f},head[u]=etot++;
        e[etot]={u,head[v],f2},head[v]=etot++;
    }

    bool bfs(){
        for(int i=1;i<=vtot;++i){
            dis[i]=0;
            cur[i]=head[i];
        }
        queue<int> q;
        q.push(s);
        dis[s]=1;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int i=head[u];~i;i=e[i].nxt){
                if(e[i].f&&!dis[e[i].v]){
                    int v=e[i].v;
                    dis[v]=dis[u]+1;
                    if(v==t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u,T m){
        if(u==t) return m;
        T flow=0;
        for(int i=cur[u];~i;cur[u]=i=e[i].nxt){
            if(e[i].f&&dis[e[i].v]==dis[u]+1){
                T f=dfs(e[i].v,min(m,e[i].f));
                e[i].f-=f;
                m-=f;
                e[i^1].f+=f;
                flow+=f;
                if(!m) break;
            }
        }
        if(!flow) dis[u]=-1;
        return flow;
    }

    T dinic(){
        T flow=0;
        while(bfs()) flow+=dfs(s,numeric_limits<T>::max());
        return flow;
    }

    void init(int s_,int t_,int vtot_){
        s=s_;
        t=t_;
        vtot=vtot_;
        etot=0;
        for(int i=1;i<=vtot;++i) head[i]=-1;
    }
};

FlowGraph<ll> g;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    scanf("%d%d",&n,&m);
    int s=2,t=2*n-1;
    g.init(s,t,t);
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        g.add(2*u,2*v-1,inf);
        g.add(2*v,2*u-1,inf);
    }
    for(int i=1;i<=n;++i){
        int c;
        scanf("%d",&c);
        g.add(2*i-1,2*i,c);
    }
    printf("%lld\n",g.dinic());
    vector<int> ans;
    //dis!=0在s，dis=0在t
    for(int i=1;i<=n;++i){
        if(g.dis[i*2-1]>0&&g.dis[i*2]==0) ans.push_back(i);
    }
    printf("%d\n",(int)ans.size());
    for(auto cur:ans) printf("%d ",cur);
    return 0;
} 
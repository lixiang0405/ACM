/*
给定一个边带正权的连通无向图 G=(V,E)，其中 n=|V|,m=|E|，n 个点从 1 到 n 依次编号。

给定三个正整数 u,v,L(u≠v)，假设现在加入一条边权为 L 的边 (u,v)，

那么需要删掉最少多少条边，才能够使得这条边既可能出现在最小生成树上，

也可能出现在最大生成树上？
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

FlowGraph<int> g;
array<int,3> e[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
       scanf("%d%d%d",&e[i][0],&e[i][1],&e[i][2]);
    }
    int s,t,w;
    scanf("%d%d%d",&s,&t,&w);
    g.init(s,t,n);
    for(int i=1;i<=m;++i){
        if(e[i][2]<w) g.add(e[i][0],e[i][1],1,1);
    }
    int ans1=g.dinic();
    g.init(s,t,n);
    for(int i=1;i<=m;++i){
        if(e[i][2]>w) g.add(e[i][0],e[i][1],1,1);
    }
    int ans2=g.dinic();
    printf("%d",ans1+ans2);
    return 0;
} 
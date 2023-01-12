//给定 n 个点，m 条有向边，给定每条边的容量，求从点 s 到点 t 的最大流。

const int V=1010;//节点个数
const int E=10100;//边个数
template<typename T>
struct FlowGraph{
    int s,t,vtot;
    int head[V],etot;
    int dis[V],cur[V];
    struct edge{
        int v,nxt;
        T f;
    }e[E*2];

    void addedge(int u,int v,T f){
        e[etot]={v,head[u],f},head[u]=etot++;
        e[etot]={u,head[v],0},head[v]=etot++;
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
        for(int i=1;i<=vtot;++i) head[i]=-1;
    }
};

FlowGraph<ll> g;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	g.init(s,t,n);
	for(int i=1;i<=m;++i){
		int u,v,f;
		scanf("%d%d%d",&u,&v,&f);
		g.addedge(u,v,f);
	}
	printf("%lld",g.dinic());
	return 0;
} 
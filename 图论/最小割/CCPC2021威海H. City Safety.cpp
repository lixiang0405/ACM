/*
题意:一棵树,加强第 i 个点有 wi 的花费,而如果距离某
个点 ≤ p 的所有点都加强了,则会有 vp 的收益,求最大净收益。
*/

/*
最大权闭合子图

转化为最小割。先把所有收益加到答案里。
左边的点 vi,p 表示距离第 i 个点 ≤ p 的所有点全选
右边的点 ui 表示原图的点 i
源点连向每个 vi,p,容量为增量收益 vi,p − vi,p−1,割掉这条
边表示放弃这个增量收益
每个 vi,p 连向右边距离 i 为 p 的点,容量为无穷大
每个 vi,p 连向 vi,p−1,容量为无穷大,这样使得 vi,p 间接连
向与 i 距离 < p 的点,用来限制放弃收益必须按 p 从大到小放弃
右边每个点连向汇点,容量为选这个点的代价,割掉这条边
表示付出这个点的代价
答案减去最小割。
*/

const int V=100005;//节点个数
const int E=2010000;//边个数
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
int a[N],w[N],dis[N][N],dep[N];
VI e[N];

void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	for(auto v:e[u]) if(v!=fa) dfs(v,u);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin>>n;
	rep(i,1,1+n) cin>>w[i];
	rep(i,1,1+n) cin>>a[i];
	ll ans=(ll)a[n]*n;
	rep(i,1,n){
		int u,v;
		cin>>u>>v;
		e[u].pb(v);
		e[v].pb(u);
	}
	rep(i,1,1+n){
		dfs(i,0);
		rep(j,1,1+n) dis[i][j]=dep[j]-dep[i];
	}
	int s=n*(n+1)+1,t=n*(n+1)+2;
	g.init(s,t,t);
	rep(i,1,1+n){
		rep(j,1,1+n){
			g.add(s,i*n+j,a[j]-a[j-1]);
			if(j!=1)
				g.add(i*n+j,i*n+j-1,inf);
		}
	}
	rep(i,1,1+n) g.add(i,t,w[i]);
	rep(i,1,1+n){
		rep(j,1,1+n){
			g.add(i*n+dis[i][j]+1,j,inf);
		}
	}
	cout<<ans-g.dinic();
	return 0;
}
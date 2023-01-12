/*
在一个有 m×n 个方格的棋盘中，每个方格中有一个正整数。

现要从方格中取数，使任意两个数所在方格没有公共边，且取出的数的总和最大，求最大的和。
*/

//二分图的最大权独立集
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
int n,m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	int s=n*m+1,t=n*m+2;
	g.init(s,t,t);
	int ans=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			int x;
			scanf("%d",&x);
			if((i+j)%2){
				g.add(s,(i-1)*m+j,x);
				if(i<n) g.add((i-1)*m+j,i*m+j,(1<<29));
				if(i>1) g.add((i-1)*m+j,(i-2)*m+j,(1<<29));
				if(j<m) g.add((i-1)*m+j,(i-1)*m+j+1,(1<<29));
				if(j>1) g.add((i-1)*m+j,(i-1)*m+j-1,(1<<29));
			}else{
				g.add((i-1)*m+j,t,x);
			}
			ans+=x;
		}
	}
	printf("%d",ans-g.dinic());
	return 0;
} 
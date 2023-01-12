/*
高一一班的座位表是个 n×m 的矩阵，经过一个学期的相处，每个同学和前后左右相邻的同学互相成为了好朋友。

这学期要分文理科了，每个同学对于选择文科与理科有着自己的喜悦值，而一对好朋友如果能同时选文科或者理科，那么他们又将收获一些喜悦值。作为计算机竞赛教练的scp大老板，想知道如何分配可以使得全班的喜悦值总和最大。

输入格式
第一行两个正整数n,m(1≤n,m≤100)。接下来一共六个矩阵。

前两个矩阵为 n 行 m 列，依次表示选择文科，理科获得的喜悦值。

接下来两个矩阵为 n−1 行 m 列，依次表示前后同学同时选择文科，理科的额外喜悦值。

接下来两个矩阵为 n 行 m−1 列，依次表示左右同学同时选择文科，理科的额外喜悦值。

保证所有的喜悦值为不超过 5000 的非负整数。
*/

const int V=101000;//节点个数
const int E=1010000;//边个数
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
        memset(head,-1,sizeof(head));
		//for(int i=1;i<=vtot;++i) head[i]=-1;
    }
};

FlowGraph<ll> g;
int n,m;

int id(int x,int y){
	return (x-1)*m+y+2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	ll ans=0;
	int s=1,t=2,tot=2;
	g.init(s,t,0);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			int x;
			scanf("%d",&x);
			ans+=x;
			++tot;
			g.add(s,id(i,j),x);
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			int x;
			scanf("%d",&x);
			ans+=x;
			g.add(id(i,j),t,x);
		}
	}
	for(int i=1;i<=n-1;++i){
		for(int j=1;j<=m;++j){
			int x;
			scanf("%d",&x);
			ans+=x;
			++tot;
			g.add(s,tot,x);
			g.add(tot,id(i,j),inf);
			g.add(tot,id(i+1,j),inf);
		}
	}
	for(int i=1;i<=n-1;++i){
		for(int j=1;j<=m;++j){
			int x;
			scanf("%d",&x);
			ans+=x;
			++tot;
			g.add(tot,t,x);
			g.add(id(i,j),tot,inf);
			g.add(id(i+1,j),tot,inf);
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m-1;++j){
			int x;
			scanf("%d",&x);
			ans+=x;
			++tot;
			g.add(s,tot,x);
			g.add(tot,id(i,j),inf);
			g.add(tot,id(i,j+1),inf);
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m-1;++j){
			int x;
			scanf("%d",&x);
			ans+=x;
			++tot;
			g.add(tot,t,x);
			g.add(id(i,j),tot,inf);
			g.add(id(i,j+1),tot,inf);
		}
	}
	g.vtot=tot;
	printf("%lld",ans-g.dinic());
	return 0;
} 
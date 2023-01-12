/*
假设一个试题库中有 n 道试题。每道试题都标明了所属类别。

同一道题可能有多个类别属性。现要从题库中抽取 m 道题组成试卷。

并要求试卷包含指定类型的试题。试设计一个满足要求的组卷算法。

第一行有两个整数 k,n(1≤n≤1000,2≤k≤20,k≤n)。k 表示题库中试题类型总数，n 表示题库中试题总数。第二行有 k 个正整数，第 i 个正整数表示要选出的类型 i 的题数。这 k 个数相加就是要选出的总题数 m。

接下来的 n 行给出了题库中每个试题的类型信息。每行的第一个正整数 p 表明该题可以属于 p 类，接着的 p 个数是该题所属的类型号。
*/

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
int n,k;
vector<array<int,3>> used;
vector<int> res[30];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&k,&n);
	//1-k k+1-k+n s=k+1+n t=k+2+n
	int s=k+1+n,t=k+2+n;
	g.init(s,t,t);
	ll xtot=0;
	for(int i=1;i<=k;++i){
		int x;
		scanf("%d",&x);
		g.addedge(s,i,x);
		xtot+=x; 
	}
	for(int i=1;i<=n;++i){
		int p;
		scanf("%d",&p);
		g.addedge(i+k,t,1);
		for(int j=0;j<p;++j){
			int x;
			scanf("%d",&x);
			used.push_back({x,i,g.etot});
			g.addedge(x,i+k,1);
		}
	}
	ll ans=g.dinic();
	if(ans!=xtot){
		printf("No Solution!");
		return 0;
	}
	for(auto [i,j,k]:used){
		if(g.e[k].f==0){
			res[i].push_back(j);
		}
	}
	for(int i=1;i<=k;++i){
		printf("%d: ",i);
		for(auto cur:res[i]) printf("%d ",cur);
		printf("\n");
	}
	return 0;
} 
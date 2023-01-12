/*
W 教授正在为国家航天中心计划一系列的太空飞行。

每次太空飞行可进行一系列商业性实验而获取利润。

现已确定了一个可供选择的实验集合 E={E1,E2,⋯,Em}，

和进行这些实验需要使用的全部仪器的集合 I={I1,I2,⋯,In}。

实验 Ej 需要用到的仪器是 I 的子集 Rj⊆I。

配置仪器 Ik 的费用为 ck 美元。实验 Ej 的赞助商已同意为该实验结果支付 pj 美元。

W 教授的任务是找出一个有效算法，
确定在一次太空飞行中要进行哪些实验并因此而配置哪些仪器才能使太空飞行的净收益最大。

这里净收益是指进行实验所获得的全部收入与配置仪器的全部费用的差额。

对于给定的实验和仪器配置情况，编程找出净收益最大的试验计划。
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
int n,m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin >> m >> n;
    string str;
    getline(cin, str);
	int s=m+n+1,t=m+n+2;
	ll ans=0;
	g.init(s,t,t);
    for (int i = 1; i <= m; i++) {
        getline(cin, str);

        stringstream ss;
        ss << str;

        int x;
        ss >> x;
		g.add(s,i,x);
		ans=ans+x;
        while (!ss.eof()) {
            ss >> x;
			g.add(i,m+x,inf);
		}
    }
	//算亏损的最小值
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		g.add(m+i,t,x);
	}
	ans=ans-g.dinic();
	vector<int> a,b;
	for(int i=1;i<=m;++i){
		//在s集--选了
		if(g.dis[i]>0) a.push_back(i);
	}
	for(int i=m+1;i<=m+n;++i){
		if(g.dis[i]>0) b.push_back(i-m);
	}
	for(auto cur:a) cout<<cur<<" ";
	cout<<endl;
	for(auto cur:b) cout<<cur<<" ";
	cout<<endl;
	cout<<ans<<endl;
	return 0;
} 
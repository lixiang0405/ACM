/*
https://codeforces.com/contest/1717/problem/F
哦不，在第一次考试中，小圆遇到了这个难题：
给定整数 n 和 m 整数对 (vi,ui)。
还有一个数组 b1,b2,...,bn，最初用零填充。
然后对于每个索引 i，其中 1≤i≤m，执行 bvi:=bvi−1 和 bui:=bui+1，
或 bvi:=bvi+1 和 bui:=bui−1。
请注意，每个 i 都应该执行这些操作中的一个。
还有一个长度为 n 的数组 s，由 0 和 1 组成。还有一个数组 a1,a2,...,an，
帮助 Madoka 并确定何时可以以这样的方式执行操作，即对于每个 i，其中 si=1，它保持 ai=bi。
如果可能的话，您还应该为 Madoka 提供一种执行操作的方法。
*/
const int V=10100;//节点个数
const int E=101000;//边个数
template<typename T>
struct FG{
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

FG<int> g;
int n,m,s[N],a[N];
vector<pii> e;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
	cin>>n>>m;
	rep(i,1,1+n) cin>>s[i];
	rep(i,1,1+n) cin>>a[i];
    rep(i,1,1+m){
		int u,v;
		cin>>u>>v;
		e.pb({u,v});
		a[u]++;
		a[v]--;
	}
	rep(i,1,1+n){
		if(s[i]&&a[i]%2){
			cout<<"NO\n";
			return 0;
		}
		a[i]/=2;
	}
	int S=n+1,t=n+2,tmp=n+3;
	g.init(S,t,tmp);
	rep(i,0,m){
		int u=e[i].fi,v=e[i].se;
		g.add(u,v,1);
	}
	int pos=0,neg=0;
	rep(i,1,1+n){
		if(s[i]==0){
			g.add(tmp,i,inf);
			g.add(i,tmp,inf);
		}else if(a[i]>=0){
			g.add(S,i,a[i]);
			pos+=a[i];
		}else{
			g.add(i,t,-a[i]);
			neg-=a[i];
		}
	}
	if(pos>=neg){
		g.add(tmp,t,pos-neg);
	}else{
		g.add(S,tmp,neg-pos);
	}
	if(g.dinic()!=max(pos,neg)){
		cout<<"NO\n";
		return 0;
	}
	cout<<"YES\n";
	rep(i,0,m){//流1的流量代表v减u大，不流代表u减1，v增1
		int u=e[i].fi,v=e[i].se;
		if(g.e[i*2].f){
			cout<<u<<" "<<v<<'\n';
		}else{
			cout<<v<<" "<<u<<'\n';
		}
	}
	return 0;
} 
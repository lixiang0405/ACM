/*
Dicing 是一个两人玩的游戏，这个游戏在 Byteotia 非常流行，

甚至人们专门成立了这个游戏的一个俱乐部。

俱乐部的人时常在一起玩这个游戏然后评选出玩得最好的人。

现在有一个非常不走运的家伙，他想成为那个玩的最好的人。

他现在知道了所有比赛的安排。

他想知道，比赛以后赢的最多的那个家伙至少会赢多少场。
*/
const int V=20100;//节点个数
const int E=101000;//边个数
template<typename T>
struct FlowGraph{
    int s,t,vtot;
    int head[V],etot;
    int dis[V],cur[V];
    struct edge{
        int v,nxt;
        T f;
    }e[E*2];

    void add(int u,int v,T f){
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
        etot=0;
        for(int i=1;i<=vtot;++i) head[i]=-1;
    }
};

FlowGraph<int> g;
int n,m;
int p[V][2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        int u,v;
        scanf("%d%d",&p[i][0],&p[i][1]);
    }
    //s->{n+1,n+m}->{1-n}->t  
    int s=n+m+1,t=n+m+2;
    int l=0,r=m;
    auto check=[&](int x){
        g.init(s,t,t);
        for(int i=1;i<=m;++i){
            g.add(s,n+i,1);
            g.add(n+i,p[i][0],1);
            g.add(n+i,p[i][1],1);
        }
        for(int i=1;i<=n;++i) g.add(i,t,x);
        return g.dinic()==m;
    };
    while(l<r){
        int mid=(l+r)/2;
        if(check(mid)){
            r=mid;
        }else{
            l=mid+1;
        }
    }
    printf("%d",l);
	return 0;
} 
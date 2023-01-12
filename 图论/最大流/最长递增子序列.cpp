/*
给定正整数序列 x1∼xn，以下递增子序列均为非严格递增。

计算其最长递增子序列的长度 s。
计算从给定的序列中最多可取出多少个长度为 s 的递增子序列。
如果允许在取出的序列中多次使用 x1 和 xn，则从给定序列中最多可取出多少个长度为 s 的递增子序列。
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
int a[N],dp[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<=n;++i){
        for(int j=0;j<i;++j){
            if(a[i]>=a[j]) dp[i]=max(dp[i],dp[j]+1);
        }
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
    int s=2*n+1,t=2*n+2;
    g.init(s,t,t);
    for(int i=1;i<=n;++i){
        if(dp[i]==1) g.add(s,i,n);
        if(dp[i]==ans) g.add(i+n,t,n);
        g.add(i,i+n,1);
        for(int j=i+1;j<=n;++j){
            if(a[j]>=a[i]&&dp[j]==dp[i]+1) g.add(i+n,j,1);
        }
    }
    printf("%d\n",g.dinic());
    g.init(s,t,t);
    for(int i=1;i<=n;++i){
        if(dp[i]==1) g.add(s,i,n);
        if(dp[i]==ans) g.add(i+n,t,n);
        //ans==1时如果不限流会使其最大流取到n
        if((i!=1&&i!=n)||ans==1) g.add(i,i+n,1);
        else g.add(i,i+n,n);
        for(int j=i+1;j<=n;++j){
            if(a[j]>=a[i]&&dp[j]==dp[i]+1) g.add(i+n,j,1);
        }
    }	
    printf("%d\n",g.dinic());
    return 0;
} 
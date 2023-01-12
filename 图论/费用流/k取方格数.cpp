/*
给出一个 n×n 的矩阵，每一格有一个非负整数 Ai,j。

现在从 (1,1) 出发，可以往右或者往下走，最后到达 (n,n)，

每达到一格，把该格子的数取出来，该格子的数就变成0。

这样一共走 k 次，现在要求 k 次所达到的方格的数的和最大。

对于k=1∼n都输出答案。
*/

const int V=20100;
const int E=201000;
template<typename T>
struct  MCG{
	int s,t,vtot,etot;
	int head[V],pre[V];
	T dis[V],flow,cost,pf[V];
	bool vis[V];

	struct edge{
		int v,nxt;
		T f,c;
	}e[E*2];

	void add(int u,int v,T f,T c,T f2=0){
		e[etot]={v,head[u],f,c};head[u]=etot++;
		e[etot]={u,head[v],f2,-c};head[v]=etot++;
	}

	bool spfa(){
		T inf=numeric_limits<T>::max()/2;
		for(int i=1;i<=vtot;++i){
			dis[i]=inf;
			vis[i]=false;
			pre[i]=-1;
			pf[i]=inf;
		}
		dis[s]=0;
		vis[s]=true;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int u=q.front();
			for(int i=head[u];~i;i=e[i].nxt){
				int v=e[i].v;
				if(e[i].f&&dis[v]>dis[u]+e[i].c){
					dis[v]=dis[u]+e[i].c;
					pre[v]=i;
					pf[v]=min(pf[u],e[i].f);
					if(!vis[v]){
						vis[v]=1;
						q.push(v);
					}
				}
			}
			q.pop();
			vis[u]=false;
		}
		return dis[t]!=inf;
	}

	void augment(){
		int u=t;
		//T f=pf[t];
		T f=1;//每次增广流量1并输出费用
		flow+=f;
		cost+=f*dis[t];
		u=t;
		while(~pre[u]){
			e[pre[u]].f-=f;
			e[pre[u]^1].f+=f;
			u=e[pre[u]^1].v;
		}
		printf("%lld\n",-cost);
	}

	pair<T,T> solve(){
		flow=0;
		cost=0;
		while(spfa()) augment();
		return {flow,cost};
	}

	void init(int s_,int t_,int vtot_){
		s=s_;
		t=t_;
		vtot=vtot_;
		etot=0;
		for(int i=1;i<=vtot;++i) head[i]=-1;
	}
};

int n,id[N][N];
MCG<ll> g;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	int tot=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			id[i][j]=++tot;
		}
	}
	int s=tot*2+1,t=tot*2+2;
	g.init(s,t,t);
	g.add(s,1,n,0);
	g.add(id[n][n]*2,t,n,0);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i!=n) g.add(id[i][j]*2,id[i+1][j]*2-1,inf,0);
			if(j!=n) g.add(id[i][j]*2,id[i][j+1]*2-1,inf,0);
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			int x;
			scanf("%d",&x);
			g.add(id[i][j]*2-1,id[i][j]*2,1,-x);
			g.add(id[i][j]*2-1,id[i][j]*2,inf,0);
		}
	}
	g.solve();
	return 0;
} 
/*
    2 3
   3 4 5
  9 10 9 1
 1 1 10 1 1
1 1 10 12 1 1

梯形的第一行有 m 个数字。从梯形的顶部的 m 个数字开始，在每个数字处可以沿左下或右下方向移动，形成一条从梯形的顶至底的路径。

分别遵守以下规则：

1.从梯形的顶至底的 m 条路径互不相交；

2.从梯形的顶至底的 m 条路径仅在数字结点处相交；

3.从梯形的顶至底的 m 条路径允许在数字结点相交或边相交。
*/

const int V=20100;
const int E=201000;
template<typename T>
struct  MCG{
	int s,t,vtot,etot;
	int head[V],pre[V];
	T dis[V],flow,cost;
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
		T f=numeric_limits<T>::max();
		while(~pre[u]){
			f=min(f,e[pre[u]].f);
			u=e[pre[u]^1].v;
		}
		flow+=f;
		cost+=f*dis[t];
		u=t;
		while(~pre[u]){
			e[pre[u]].f-=f;
			e[pre[u]^1].f+=f;
			u=e[pre[u]^1].v;
		}
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

MCG<ll> g1,g2,g3;
int n,m,tot=0;
int id[50][50];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m+i-1;++j){
			id[i][j]=++tot;
		}
	}
	int s=2*tot+1,t=2*tot+2;
	g1.init(s,t,t);
	g2.init(s,t,t);
	g3.init(s,t,t);
	for(int i=1;i<=m;++i){
		g1.add(s,2*id[1][i]-1,1,0);
		g2.add(s,2*id[1][i]-1,1,0);
		g3.add(s,2*id[1][i]-1,1,0);
	}
	for(int i=1;i<=m+n-1;++i){
		g1.add(2*id[n][i],t,1,0);
		g2.add(2*id[n][i],t,inf,0);
		g3.add(2*id[n][i],t,inf,0);
	}
    for(int i=1;i<=n-1;++i){
        for(int j=1;j<=m+i-1;++j){
            g1.add(2*id[i][j],2*id[i+1][j]-1,1,0);
            g1.add(2*id[i][j],2*id[i+1][j+1]-1,1,0);
            g2.add(2*id[i][j],2*id[i+1][j]-1,1,0);
            g2.add(2*id[i][j],2*id[i+1][j+1]-1,1,0);
            g3.add(2*id[i][j],2*id[i+1][j]-1,inf,0);
            g3.add(2*id[i][j],2*id[i+1][j+1]-1,inf,0);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m+i-1;++j){
            int x;
            scanf("%d",&x);
            g1.add(2*id[i][j]-1,2*id[i][j],1,-x);
            g2.add(2*id[i][j]-1,2*id[i][j],inf,-x);
            g3.add(2*id[i][j]-1,2*id[i][j],inf,-x);
        }
    }
    printf("%lld %lld %lld",-g1.solve().second,-g2.solve().second,-g3.solve().second);
	return 0;
} 
/*
https://codeforces.com/contest/1766/problem/F
给定一个由 n 个顶点和 m 条有向弧组成的图。
第 i 条弧从顶点 xi 到顶点 yi，容量为 ci，权重为 wi。
没有弧进入顶点 1，也没有弧从顶点 n 出发。
图中没有负权重的循环（不可能以这样一种方式从任何顶点行进到自身，使得你经过的所有弧的总权重为负）。
您必须为每个弧分配一个流（0 及其容量之间的整数，包括在内）。
对于除 1 和 n 之外的每个顶点，去往该顶点的弧上的总流量必须等于从该顶点去的弧上的总流量。
设第i条弧上的流量为fi，则流量成本等于∑i={1-m}fiwi。
您必须找到使成本最小化的流程。
听起来很经典，对吧？
好吧，我们对每条边上的流都有一些额外的限制：
如果ci是偶数，fi一定是偶数；
如果ci是奇数，fi一定是奇数。
你能解决这个问题吗？
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
		T f,c,p;
	}e[E*2];
 
	void add(int u,int v,T f,T c,T f2=0){
		e[etot]={v,head[u],f,c,0};head[u]=etot++;
		e[etot]={u,head[v],f2,-c,0};head[v]=etot++;
	}
    
    int rem(int x){
        return e[x].f - e[x].p;
    }

	pair<T, T> MCMF(){
        T flow = 0;
        T cost = 0;
        while(true){
            vector<T> d(vtot + 1, (T)(1e18));
            vector<int> p(vtot + 1, -1);
            vector<int> pe(vtot + 1, -1);
            queue<int> q;
            vector<bool> inq(vtot + 1);
            q.push(s);
            inq[s] = true;
            d[s] = 0;
            while(!q.empty()){
                int k = q.front();
                q.pop();
                inq[k] = false;
                for(int ei = head[k]; ~ei ; ei = e[ei].nxt){
                    if(rem(ei) == 0) continue;
                    int to = e[ei].v;
                    int w = e[ei].c;
                    if(d[to] > d[k] + w){
                        d[to] = d[k] + w;
                        p[to] = k;
                        pe[to] = ei;
                        if(!inq[to]){
                            inq[to] = true;
                            q.push(to);
                        }
                    }
                }
            }
            if(p[t] == -1 || d[t] >= 0) break;
            flow++;
            cost += d[t];
            int cur = t;
            while(cur != s){
                e[pe[cur]].p++;
                e[pe[cur] ^ 1].p--;
                cur = p[cur];
            }
        }
        return {flow, cost};
    }
 
	void init(int s_,int t_,int vtot_){
		s=s_;
		t=t_;
		vtot=vtot_;
		etot=0;
		for(int i=1;i<=vtot;++i) head[i]=-1;
	}
};
 
MCG<int> g;
int out[N],res[N],rec[N];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	int ans=0;
	int s=n+1,t=n+2;
	g.init(s,t,t);
	rep(i,1,1+m){
		int x,y,c,w;
		cin>>x>>y>>c>>w;
		if(c%2){
			res[i]++;
			ans+=c;
			out[x]++;
			out[y]--;
		}
		g.add(x,y,c/2,w);//[0,w/2]
        rec[i]=g.etot-2;
	}
	if((out[1])%2){
		out[1]++;
		out[n]--;
	}
	rep(i,1,1+n){
		if((out[i])%2){
			cout<<"Impossible\n";
			return 0;
		}
		if(out[i]<=0){
			g.add(s,i,-out[i]/2,-inf);
		}else if(out[i]>0){
			g.add(i,t,out[i]/2,-inf);
		}
	}
	g.add(s,1,inf,0);
    g.add(n,t,inf,0);
	ans+=g.MCMF().se;
	rep(i,0,g.etot){
		if(g.e[i].c==-inf&&g.rem(i)){
            cout<<"Impossible\n";
            return 0;
		}
	}
	cout<<"Possible\n";
	rep(i,1,1+m){
		cout<<g.e[rec[i]].p*2+res[i]<<" ";
	}
    return 0;
}

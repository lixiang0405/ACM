/*
由于对Farmer John的领导感到极其不悦，奶牛们退出了农场，组建了奶牛议会。

议会以“每头牛 都可以获得自己想要的”为原则，建立了下面的投票系统：

M 只到场的奶牛会给 N 个议案投票。每只奶牛会对恰好两个议案Bi,Ci投出Y或N，

分别表示赞成和反对。最后，议案会以如下的方式决定：

每只奶牛投出的两票中至少有一票和最终结果相符合。

例如Bessie给议案1投了赞成Y，给议案2投了反对N，那么在任何合法的议案通过方案中，

必须满足议案1必须是Y或者议案2必须是N，或者同时满足。

给出每只奶牛的投票，你的工作是确定哪些议案可以通过，哪些不能。

如果不存在这样一个方案，输出IMPOSSIBLE。

对于一个议案，如果在所有方案里面都能通过，输出Y。

如果在所有方案里面都不能能通过，输出N，否则输出问号?。
*/

int t;

int n,m,cnt=0,tot=0;
int dfn[N],low[N],bel[N],sz[N],ins[N],vis[N];
stack<int> sk;
vector<int> e[N];
 
void dfs(int u){
	dfn[u]=low[u]=++tot;
	sk.push(u);
	ins[u]=1;
	for(auto v:e[u]){
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else 
			if(ins[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		++cnt;
		while(1){
			int x=sk.top();
			sk.pop();
			ins[x]=0;
			bel[x]=cnt;
			sz[cnt]++;
			if(x==u) break;
		}
	}
}

bool is(int u,int v){
    rep(i,0,2*n) vis[i]=0;
    queue<int> q;
    q.push(u);
    vis[u]=1;
    while(!q.empty()){
        u=q.front();
        q.pop();
        for(auto cur:e[u]){
            if(cur==v) return true;
            if(vis[cur]) continue;
            q.push(cur);
            vis[cur]=1;
        }
    }
    return false;
}

void solve(){
    cin>>n>>m;
    rep(i,0,m){
        int u,v;
        char c;
        cin>>u>>c;
        u--;
        u=u*2+(c=='Y');//Y是1
        cin>>v>>c;
        v--;
        v=v*2+(c=='Y');
        e[u^1].pb(v);
        e[v^1].pb(u);
    }
    rep(i,0,2*n) if(!dfn[i]) dfs(i);
    rep(i,0,n) 
        if(bel[2*i]==bel[2*i+1]){
            cout<<"IMPOSSIBLE\n";
            return;
        }
    string ans;
    ans.resize(n);
    rep(i,0,n){//2*i->2*i+1不能取2*i
        if(is(2*i,2*i+1)) ans[i]='Y';
        else if(is(2*i+1,2*i)) ans[i]='N';
        else ans[i]='?';
    }
    cout<<ans<<'\n';
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
    t=1;
    while(t--){
        solve();
    }
    return 0;
} 

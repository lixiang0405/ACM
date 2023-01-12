/*
小 L 计划进行 n 场游戏，每场游戏使用一张地图，小 L 会选择一辆车在该地图上完成游戏。

小 L 的赛车有三辆，分别用大写字母 A、B、C 表示。地图一共有四种，分别用小写字母 x、a、b、c 表示。

其中，赛车 A 不适合在地图 a 上使用，赛车 B 不适合在地图 b 上使用，赛车 C 不适合在地图 c 上使用，

而地图 x 则适合所有赛车参加。

适合所有赛车参加的地图并不多见，最多只会有 d 张。

n 场游戏的地图可以用一个小写字母组成的字符串描述。

例如：S=xaabxcbc 表示小L计划进行 8 场游戏，其中第 1 场和第 5 场的地图类型是 x，

适合所有赛车，第 2 场和第 3 场的地图是 a，不适合赛车 A，第 4 场和第 7 场的地图是 b，

不适合赛车 B，第 6 场和第 8 场的地图是 c，不适合赛车 C。

小 L 对游戏有一些特殊的要求，这些要求可以用四元组 (i,hi,j,hj) 来描述，

表示若在第 i 场使用型号为 hi 的车子，则第 j 场游戏要使用型号为 hj 的车子。

你能帮小 L 选择每场游戏使用的赛车吗？如果有多种方案，输出任意一种方案。

如果无解，输出 -1。
*/

int t;

int n,d,m,cnt=0,tot=0;
int dfn[N],low[N],bel[N],sz[N],ins[N],vis[N];
stack<int> sk;
vector<int> e[N];
vector<array<int,4>> E;
string s;
 
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

bool solve(){
    rep(i,0,2*n) dfn[i]=0,e[i].clear();
    tot=cnt=0;
    auto getid=[&](int x,int y){
        if(s[x]-'a'==y) return -1;
        if(s[x]=='a'){
            return 2*x+(y==1);
        }else if(s[x]=='b'){
            return 2*x+(y==0);
        }else{
            return 2*x+(y==0);
        }
    };
    for(auto [u,a,v,b]:E){
        u=getid(u,a);
        v=getid(v,b);
        if(u!=-1&&v!=-1){
            e[u].pb(v);
            e[v^1].pb(u^1);
        }else if(u!=-1&&v==-1){//u一定不成立
            e[u].pb(u^1);
        }
    }
    rep(i,0,2*n) if(!dfn[i]) dfs(i);
    rep(i,0,n) 
        if(bel[2*i]==bel[2*i+1]){
            return false;
        }
    string ans;
    ans.resize(n);
    rep(i,0,n){
       if(bel[2*i]<bel[2*i+1]){
            if(s[i]=='a'){
                ans[i]='C';
            }else if(s[i]=='b'){
                ans[i]='C';
            }else{
                ans[i]='B';
            }
       }else{
            if(s[i]=='a'){
                ans[i]='B';
            }else if(s[i]=='b'){
                ans[i]='A';
            }else{
                ans[i]='A';
            }
       } 
    }
    cout<<ans<<'\n';
    return true;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);         
    cin>>n>>d>>s>>m;
    VI vt;
    rep(i,0,n) if(s[i]=='x') vt.pb(i);
    rep(i,0,m){
        int u,v;
        char a,b;
        cin>>u>>a>>v>>b;
        u--,v--;
        E.pb({u,a-'A',v,b-'A'});
    }
    //0 AB 1 AC
    rep(i,0,1<<d){
        rep(j,0,d){
            if(i&(1<<j)) s[vt[j]]='b';//可以取AC
            else s[vt[j]]='c';// 可以取AB
        }
        if(solve()) return 0;
    }
    cout<<-1<<'\n';
    return 0;
} 

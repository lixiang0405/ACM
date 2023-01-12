/*
整座宫殿呈矩阵状，由R×C间矩形宫室组成，其中有N间宫室里埋藏着宝藏，称作藏宝宫室。

宫殿里外、相邻宫室间都由坚硬的实体墙阻隔，由一间宫室到达另一间只能通过所驼门王独创的移动方式——传送门。

所驼门王为这N间藏宝宫室每间都架设了一扇传送门，没有宝藏的宫室不设传送门，所有的宫室传送门分为三种：

“横天门”：由该门可以传送到同行的任一宫室；

“纵寰门”：由该门可以传送到同列的任一宫室；

“任意门”：由该门可以传送到以该门所在宫室为中心周围8格中任一宫室（如果目标宫室存在的话）。

深谋远虑的Henry当然事先就搞到了所驼门王当年的宫殿招标册，书册上详细记录了每扇传送门所属宫室及类型。

而且，虽然宫殿内外相隔，但他自行准备了一种便携式传送门，可将自己传送到殿内任意一间宫室开始寻宝，

并在任意一间宫室结束后传送出宫。整座宫殿只许进出一次，且便携门无法进行宫室之间的传送。

不过好在宫室内传送门的使用没有次数限制，每间宫室也可以多次出入。

现在Henry已经打开了便携门，即将选择一间宫室进入。为得到尽多宝藏，他希望安排一条路线，

使走过的不同藏宝宫室尽可能多。请你告诉Henry这条路线最多行经不同藏宝宫室的数目。
*/
const int N = 2e5+5;//至少开两倍

int n,m,cnt=0,tot=0,R,C,ans=0,p=0;
int dfn[N],low[N],bel[N],ins[N],ty[N],x[N],y[N];
map<int,vector<int>> r,c;
map<int,int> ex,ey; 
map<pair<int,int>,int> vis;
int dp[N];
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
		int sz=0;
		//dp[cnt]=0;
		while(1){
			int x=sk.top();
			sk.pop();
			ins[x]=0;
			bel[x]=cnt;
			for(auto y:e[x]){
				if(bel[y]!=cnt&&bel[y]!=0)
					dp[cnt]=max(dp[cnt],dp[bel[y]]);
			}
			sz+=(x<=n);
			if(x==u) break;
		}
		dp[cnt]+=sz;
		ans=max(ans,dp[cnt]);
	}
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d%d",&n,&R,&C);
	for(int i=1;i<=n;++i){
		scanf("%d%d%d",&x[i],&y[i],&ty[i]);
		r[x[i]].push_back(i);
		c[y[i]].push_back(i);
		vis[{x[i],y[i]}]=i;
	}
	p=n;
	for(int i=1;i<=n;++i){
		if(ty[i]==1){
			if(!ex.count(x[i])){
				ex[x[i]]=++p;
				for(auto cur:r[x[i]]) e[p].push_back(cur);
			}
			e[i].push_back(ex[x[i]]);
		}else if(ty[i]==2){
			if(!ey.count(y[i])){
				ey[y[i]]=++p;
				for(auto cur:c[y[i]]) e[p].push_back(cur);
			}
			e[i].push_back(ey[y[i]]);
		}else{
			for(int j=-1;j<=1;++j){
				for(int k=-1;k<=1;++k){
					if(j==0&&k==0) continue;
					if(vis.count({x[i]+j,y[i]+k})) e[i].push_back(vis[{x[i]+j,y[i]+k}]);
				}
			}
		}
	}
	for(int i=1;i<=p;++i)
		if(!dfn[i]) dfs(i);
	printf("%d",ans);
    return 0;
}
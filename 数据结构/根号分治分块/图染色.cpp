/*给一个n个点m条边的图，每个点一开始都是白色。

要求支持q个操作：

1 x，翻转x点的颜色，从黑到白，从白到黑。

2 x，查询x点周围有多少黑色的邻居。*/

vector<int> p[N],bigdot[N];
int ans[N],n,m,q,col[N];

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d%d",&n,&m,&q);
	for(int i=0;i<m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		p[u].push_back(v);
		p[v].push_back(u);
	}
	for(int i=1;i<=n;++i){
		if(p[i].size()>M)
		for(auto &v:p[i])
		bigdot[v].push_back(i);
	}
	for(int i=0;i<q;++i){
		int ty,x;
		scanf("%d%d",&ty,&x);
		if(ty==1){
			col[x]^=1;
			for(auto &v:bigdot[x])
			if(col[x])
			ans[v]++;
			else ans[v]--;
		}else{
			if(p[x].size()>M) printf("%d\n",ans[x]);
			else{
				int res=0;
				for(auto &v:p[x])
				res+=col[v];
				printf("%d\n",res);
			}
		}
	}
	return 0;
}

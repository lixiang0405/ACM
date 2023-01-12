/*
给你一棵根在顶点1上的有根树。每个顶点都用某种颜色着色。
如果没有其他颜色出现在顶点v的子树中的次数超过颜色c。
我们把颜色c称为顶点v子树中的主色
因此，在某个顶点的子树中，可能有两种或更多的颜色占主导地位。
顶点v的子树是顶点v
在根的每条路径中包含顶点v的所有其他顶点。
对于每个顶点v，求顶点v子树中所有主色的和
*/

/*求每棵子树出现最多的颜色的数量*/
int maxx;
int l[N],r[N],id[N],sz[N],hs[N],tot,n,c[N],cnt[N];
vector<int> e[N];
ll ans[N],maxcnt;
void dfs(int u,int f){
    l[u]=++tot;
    id[tot]=u;
    sz[u]=1;
    hs[u]=-1;
    for(auto v:e[u]){
        if(v==f) continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(hs[u]==-1||sz[v]>sz[hs[u]])
        hs[u]=v;
    }
    r[u]=tot;
}

void dsu(int u,int f,bool keep){
    for(auto v:e[u]){
        if(v!=f&&v!=hs[u])
        dsu(v,u,false);
    }
    if(hs[u]!=-1){
        dsu(hs[u],u,true);
    }
	auto add=[&](int x){
		cnt[c[x]]++;
		if(cnt[c[x]]>maxx){
			maxx=cnt[c[x]];
			maxcnt=c[x];
		}else if(cnt[c[x]]==maxx){
			maxcnt=maxcnt+c[x];
		}
	};
	auto del=[&](int x){
		cnt[c[x]]--;
	};
    for(auto v:e[u]){
        if(v!=f&&v!=hs[u]){
            for(int i=l[v];i<=r[v];++i)
            add(id[i]);
        }
    }
    add(u);
	ans[u]=maxcnt;
    if(!keep){
		maxcnt=0,maxx=0;
        for(int i=l[u];i<=r[u];++i)
        del(id[i]);
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&c[i]);
	}
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,0);
	dsu(1,0,false);
	for(int i=1;i<=n;++i)
	printf("%lld ",ans[i]);
    return 0;
}
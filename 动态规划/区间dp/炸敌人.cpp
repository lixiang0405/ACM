/*
来自外太空的外星人（终于！）入侵了地球。
保护自己，或被瓦解！或同化。或者吃掉了。我们还不确定。
外星人遵循已知的攻击模式。
有 n 个攻击者，第 i 个攻击者出现在 ai 时间，距离你有距离 di。
必须在bi之前消灭他，否则他会开枪，这肯定会结束战斗。
你的武器是一个区域冲击波，可以设置为任何给定的功率。
如果用能量 R 发射，它会瞬间摧毁距离 R 或更小的所有外星人。
它还消耗 R 燃料电池。
确定在不被杀死的情况下消灭所有外星人的最低成本（以燃料电池为单位）。
*/

int t,l[N],r[N],a[N],dp[N][N];
int n;

int dfs(int L,int R){
	if(L>R) return 0;
	if(dp[L][R]!=-1) return dp[L][R];
	int maxx=0,idx=-1;
	for(int i=1;i<=n;++i){
		if(l[i]>=L&&r[i]<=R){
			if(maxx<a[i]){
				maxx=a[i];
				idx=i;
			}
		}
	}
	if(idx==-1) return dp[L][R]=0;
	dp[L][R]=inf;
	for(int i=l[idx];i<=r[idx];++i){
		dp[L][R]=min(dp[L][R],dfs(L,i-1)+dfs(i+1,R)+a[idx]);
	}
	//cout<<L<<" "<<R<<" "<<dp[L][R]<<endl;
	return dp[L][R];
}

void solve(){
	scanf("%d",&n);
	vector<int> vt;
	for(int i=1;i<=2*n;++i){
		for(int j=i;j<=2*n;++j) dp[i][j]=-1;
	}
	for(int i=1;i<=n;++i) scanf("%d%d%d",&l[i],&r[i],&a[i]),vt.push_back(l[i]),vt.push_back(r[i]);
	stable_sort(vt.begin(),vt.end());
	vt.erase(unique(vt.begin(),vt.end()),vt.end());
	for(int i=1;i<=n;++i){
		l[i]=lower_bound(vt.begin(),vt.end(),l[i])-vt.begin()+1;
		r[i]=lower_bound(vt.begin(),vt.end(),r[i])-vt.begin()+1;
		//cout<<i<<" "<<l[i]<<" "<<r[i]<<endl;
	}
	//cout<<vt.size()<<endl;
	printf("%d\n",dfs(1,vt.size()));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&t);
	while(t--){
		solve();
	}
    return 0;
}
//有一个长为n的序列A1,A2,…,An。
//定义一个序列{A}是好的， 当且仅当他的每一个子区间[l,r]满足，至少存在一个元素x仅出现了一次。
 
int t,n,a[N],nxt[N],pre[N];

bool dfs(int l,int r){
	if(l>=r)
	return true;
	for(int i=l,j=r;i<=j;i++,j--){
		if(pre[i]<l&&nxt[i]>r) 
		return dfs(l,i-1)&&dfs(i+1,r);
		else if(pre[j]<l&&nxt[j]>r) 
		return dfs(l,j-1)&&dfs(j+1,r);
	}
	return false;
}

void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	scanf("%d",&a[i]);
	gp_hash_table<int,int> pos;
	//printf("a");
	for(int i=1;i<=n;++i){
		if(pos.find(a[i])!=pos.end()) pre[i]=pos[a[i]];
		else pre[i]=0;
		pos[a[i]]=i;
	}
	pos.clear();
	for(int i=n;i>=1;--i){
		if(pos.find(a[i])!=pos.end()) nxt[i]=pos[a[i]];
		else nxt[i]=n+1;
		pos[a[i]]=i;
	}
	puts(dfs(1,n)?"non-boring":"boring");
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
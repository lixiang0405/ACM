//给定一个1∼n的排列a1,a2,a3,…,an，想知道所有的区间[l,r]满足r−l+1≥k，这样的区间里的数中第k大的元素，输出它们的和。

int n,k,pos[N],l[N],r[N],left[N],right[N];
ll ans=0;
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i){
		int p;
		scanf("%d",&p);
		pos[p]=i;
	}
	for(int i=0;i<=n+1;++i){
		l[i]=max(i-1,0);
		r[i]=min(n+1,i+1);
	}
	for(int i=1;i<=n;++i){
		int x=pos[i];
		left[0]=x;
		for(int j=1;j<=k;++j){
			x=l[x];
			left[j]=x;
		}
		x=pos[i];
		right[0]=x;
		for(int j=1;j<=k;++j){
			x=r[x];
			right[j]=x;
		}
		x=pos[i];
		r[l[x]]=r[x];
		l[r[x]]=l[x];
		ll seg=0;
		for(int j=1;j<=k;++j){
			seg+=1ll*(left[j-1]-left[j])*(right[k-j+1]-right[k-j]);
		}
		ans+=seg*i;
	}
	printf("%lld",ans);
    return 0;
}

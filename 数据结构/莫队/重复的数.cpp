/*给定一个数列A=(a1,a2,…,an)，给出若干询问，每次询问某个区间[li,ri]内恰好出现ki次的数有多少个。*/
int n,m,ans[N],c[N],cnt[N],tmp=0,kk[N];
array<int,4> q[N];

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&c[i]);
	}
	scanf("%d",&m);
	for(int i=0;i<m;++i){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		q[i]={l,r,i,k};
	}
	stable_sort(q,q+m,[&](array<int,4> a,array<int,4> b){
		int x=a[0]/M,y=b[0]/M;
		if(x!=y) return x<y;
		else if(x%2) return a[1]>b[1];
		else return a[1]<b[1];
	});//先左端点按块分，再按右端点排序 偶数块从小到大，奇数块从大到小
	int l=1,r=0;
	auto add=[&](int x){ //(n-1)*(n)/2=1+2+3+...+n-1
		kk[cnt[c[x]]]--;
		cnt[c[x]]++;
		kk[cnt[c[x]]]++;
	};
	auto del=[&](int x){
		kk[cnt[c[x]]]--;
		cnt[c[x]]--;
		kk[cnt[c[x]]]++;	
	};
	for(int i=0;i<m;++i){
		int k=q[i][3];
		while(q[i][1]>r) r++,add(r);
		while(q[i][0]<l) l--,add(l);
		while(q[i][1]<r) del(r),r--;
		while(q[i][0]>l) del(l),l++;
		ans[q[i][2]]=kk[k];
	}
	for(int i=0;i<m;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}

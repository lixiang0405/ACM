/*作为一个生活散漫的人，

小Z每天早上都要耗费很久从一堆五颜六色的袜子中找出一双来穿。

终于有一天，小Z再也无法忍受这恼人的找袜子过程，于是他决定听天由命……

具体来说，小Z把这N只袜子从1到N编号，然后从编号L到R选出两个袜子。

尽管小Z并不在意两只袜子是不是完整的一双，甚至不在意两只袜子是否一左一右，他却很在意袜子的颜色，

毕竟穿两只不同色的袜子会很尴尬。

你的任务便是告诉小Z，他有多大的概率抽到两只颜色相同的袜子。

当然，小Z希望这个概率尽量高，所以他可能会询问多个(L,R)以方便自己选择。*/

template <typename T> void inline read(T& x) {
	int f = 1; x = 0; char s = getchar();
	while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
	while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
	x *= f;
}

ll gcd(ll a,ll b){
	return b==0?a:gcd(b,a%b);
}

int n,m,ans[N],res[N],tmp,c[N],cnt[N];
array<int,3> q[N];

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&c[i]);
	}
	for(int i=0;i<m;++i){
		int l,r;
		scanf("%d%d",&l,&r);
		q[i]={l,r,i};
		res[i]=(ll)(r-l+1)*(r-l)/2;
	}
	/*
	stable_sort(q,q+m,[&](auto &a,auto &b){
		int x=a[0]/M,y=b[0]/M;
		if(x!=y) return x<y;
		else if(a[0]%2) return a[1]>b[1];
		else return a[1]<b[1];
	});*/
	stable_sort(q,q+m,[&](array<int,3> a,array<int,3> b){
		int x=a[0]/M,y=b[0]/M;
		if(x!=y) return x<y;
		else if(x%2) return a[1]>b[1];
		else return a[1]<b[1];
	});//先左端点按块分，再按右端点排序 偶数块从小到大，奇数块从大到小
	int l=1,r=0;
	auto add=[&](int x){
		tmp+=cnt[c[x]]; //(n-1)*(n)/2=1+2+3+...+n-1
		cnt[c[x]]++;
	};
	auto del=[&](int x){
		cnt[c[x]]--;
		tmp-=cnt[c[x]];
	};
	for(int i=0;i<m;++i){
		while(q[i][1]>r) r++,add(r);
		while(q[i][0]<l) l--,add(l);
		while(q[i][1]<r) del(r),r--;
		while(q[i][0]>l) del(l),l++;
		ans[q[i][2]]=tmp;
	}
	for(int i=0;i<m;++i){
		int d=gcd(res[i],ans[i]);
		printf("%d/%d\n",ans[i]/d,res[i]/d);
	}
	return 0;
}

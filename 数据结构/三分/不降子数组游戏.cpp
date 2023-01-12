/*Yuto和Platina准备玩一个不降子数组游戏.

具体的, 给定一个长度为N的数组A, 和区间限制L和R.

Yuto首先在[L,R]中选择一个数字, 并展示给Platina看.

随后Platina也会选择一个在[L,R]中的数字.

我们不妨设Yuto选择了数字a, Platina选择了数字b.

这局游戏的得分是A[min(a,b):max(a,b)]的不降子数组的个数. (A[l:r]表示由数组A下标从l到r这一连续段构成的新数组).

注 : 数组B的子数组是从B的头尾连续删除若干(可以为空)个元素后得到的新数组.

Yuto想要得分尽可能的小, Platina想要得分尽可能的大.

他们将会在一个数组上游戏Q次, 对于每次游戏, 请输出最后游戏的得分.*/

const int N = 5e5+5;

int n,t,a[N];
int L,R;
int ble[N],st[N],ed[N];
ll pre[N];

void build(){
	int cnt=1;
	ble[1]=1,st[1]=1;
	int last=a[1];
	for(int i=2;i<=n;++i){
		if(a[i]>=last) last=a[i];
		else{
			ed[cnt]=i-1;
			cnt++;
			st[cnt]=i;
			last=a[i];
		}
		ble[i]=cnt;
	}
	ed[cnt]=n;
	for(int i=1;i<=cnt;++i) pre[i]=pre[i-1]+(ll)(ed[i]-st[i]+1)*(ed[i]-st[i]+2)/2;
	//for(int i=1;i<=cnt;++i) cout<<pre[i]<<endl;
}

ll f(int l,int r){
	if(ble[l]==ble[r]) return (ll)(r-l+1)*(r-l+2)/2;
	else{
		return pre[ble[r]-1]-pre[ble[l]]+(ll)(ed[ble[l]]-l+1)*(ed[ble[l]]-l+2)/2+(ll)(r-st[ble[r]]+1)*(r-st[ble[r]]+2)/2;
	}
}  

ll calc(int x){
	return max(f(L,x),f(x,R));
}

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>n>>t;
	for(int i=1;i<=n;++i) cin>>a[i];
	build();
	while(t--){
		int l,r;
		cin>>L>>R;
		l=L,r=R;
		//for(int i=l;i<=r;++i) cout<<calc(i)<<" ";
		//cout<<endl;
		ll ans=1e18;
		while(l!=r){
			int midl=l-(l-r)/2;
			int midr=(r+midl)/2;
			ll f1=calc(midl),f2=calc(midr);
			ans=min({f1,f2,ans});
			if(f1>f2) l=midl;
			else r=midr; 
		}
		ans=min(ans,calc(l));
		//cout<<l<<endl;
		cout<<ans<<endl;
	}
    return 0;
}

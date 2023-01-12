/*
对于序列 A，它的逆序对数定义为满足 i<j，且 Ai>Aj 的数对 (i,j) 的个数。

给 1∼n 的一个排列，按照某种顺序依次删除 m 个元素，你的任务是在每次删除一个元素之前统计整个序列的逆序对数。
*/

#define lowbit(x) x&(-x)
template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){
        n=s;
        for(int i=1;i<=n;++i) c[i]=0;
    }

    T query(int x){
        assert(x<=n);
        T s=0;
        for(;x;x-=lowbit(x)){
            s+=c[x];
        }
        return s;
    }

    void modify(int x,T s){
        assert(x!=0);
        for(;x<=n;x+=lowbit(x)){
            c[x]+=s;
        }
    }
 
    //树状数组上二分 查询最大的T(0≤T≤n)满足∑(i=1-T) ai≤s。
    int ask(T s){
        int pos=n;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos-(1<<i)<=n&&c[pos-(1<<i)]<=s){
                pos-=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};

BIT<int> c;
int a[N],pos[N],t[N];

vector<ll> solve(vector<array<int,4>> &a){
	int n=SZ(a);
	vector<ll> ans(1+n);
	function<void(int,int)> solve=[&](int l,int r){
		if(l==r) return;
		int m=(l+r)/2;
		solve(l,m);
		solve(m+1,r);
		int L=l,R=m+1;
		vector<array<int,4>> tmp;
		while(L!=m+1||R!=r+1){
			if(L!=m+1&&(R==r+1||pii(a[L][1],a[L][2])<=pii(a[R][1],a[R][2]))){
				c.modify(a[L][2],1);
				tmp.pb(a[L]);
				L++;
			}else{
				ans[a[R][3]]+=c.query(a[R][2]);
				tmp.pb(a[R]);
				R++;
			}
		}
		rep(i,l,m+1){
			c.modify(a[i][2],-1);
		}
		rep(i,l,r+1) a[i]=tmp[i-l];
	};
	sort(all(a));
	solve(0,n-1);
	return ans;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	c.resize(n);
	rep(i,1,1+n) cin>>a[i],pos[a[i]]=i;
	rep(i,1,1+m){
		int x;
		cin>>x;
		t[pos[x]]=i;
	}
	int cnt=m;
	rep(i,1,1+n){
		if(!t[pos[i]]) t[pos[i]]=++cnt;
	}
	vector<array<int,4>> tmp;
	//前面的点对后面的点有贡献，算答案算到前面的点里面
	rep(i,1,1+n){
		tmp.pb({n+1-t[i],i,n+1-a[i],t[i]});
	}
	auto ans1=solve(tmp);
	tmp.clear();
	rep(i,1,1+n){
		tmp.pb({n+1-t[i],n+1-i,a[i],t[i]});
	}
	auto ans2=solve(tmp);
	vector<ll> ans(n+1);
	rep(i,1,1+n) ans[i]=ans1[i]+ans2[i];
	per(i,1,n) ans[i]+=ans[i+1];
	rep(i,1,1+m){
		cout<<ans[i]<<'\n';
	}
	return 0;
}
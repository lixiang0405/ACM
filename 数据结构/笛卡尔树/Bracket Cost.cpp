/*给你一个长度为 n 的括号序列。
我们能对一个括号序列做以下操作：
选择一个子串，将其循环右移一位。比如，(()) 循环右移一位之后变为 )(()。
在括号序列的任意位置加一个左括号或右括号。
我们定义一个括号序列的代价为能将其变为匹配序列的最少操作次数。
求这个括号序列所有n(n+1)/2的子串的代价之和。（子串互相独立）
多组数据。n<=2e5 */

//对于一个串res=min(-premin,0)+max(tot,0) ( +1 , ) -1
//res=max(L,R)−X(已经匹配的括号)
int t;
ll pre[N],rec[N];

int root,l[N],r[N],stk[N];
int n,tot=0;
ll ans=0,a[N];

void dfs(int u,int L,int R){
	ans-=a[u]*(R-u+1)*(u-L);
	rec[L-1]+=R-u+1;
	rec[u-1]-=R-u+1;
	if(l[u]) dfs(l[u],L,u-1);
	if(r[u]) dfs(r[u],u+1,R);
}

void build(){
    int top=0;
    for(int i=1;i<=n+1;++i) l[i]=r[i]=0;
	rep(i,1,2+n) a[i]=pre[i-1];
    for(int i=1;i<=1+n;++i){
        int k=top;
        while(k>0&&a[stk[k-1]]>a[i]) --k;
        if(k) r[stk[k-1]]=i;
        if(k<top) l[i]=stk[k];
        stk[k++]=i;
        top=k;
    }
	dfs(stk[0],1,1+n);
}

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

BIT<ll> c,d;

void solve(){
	cin>>n;
	string s;
	cin>>s;
	ans=0;
	rep(i,0,n){
		if(s[i]=='(') pre[i+1]=pre[i]+1;
		else pre[i+1]=pre[i]-1;
	}
	rep(i,0,1+n) rec[i]=0;
	build();
	rep(i,1,1+n) rec[i]+=rec[i-1];
	rep(i,1,1+n){
		ans+=rec[i]*pre[i];
	}
	rep(i,1,2+n) a[i]+=n+10;
	c.resize(*max_element(a+1,a+2+n));
	d.resize(*max_element(a+1,a+2+n));	
	rep(i,1,2+n){
		ans+=d.query(a[i])*a[i]-c.query(a[i]);
		d.modify(a[i],1);
		c.modify(a[i],a[i]);
	}
	cout<<ans<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}


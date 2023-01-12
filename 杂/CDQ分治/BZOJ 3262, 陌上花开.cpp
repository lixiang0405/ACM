/*
有 n 朵花，每朵花有三个属性：花形(s)，颜色(c)，气味(m)，用三个整数表示。

现在要对每朵花评级，一朵花的级别是它拥有的美丽能超过的花的数量。

定义一朵花 A 比另一朵花 B 要美丽,当且仅 Sa≥Sb,Ca≥Cb,Ma≥Mb。
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
int ans[N];
array<int,5> a[N];

void solve(int l,int r){
	if(l==r) return;
	int m=(l+r)/2;
	solve(l,m);
	solve(m+1,r);
	int L=l,R=m+1;
	vector<array<int,5>> tmp;
	while(L!=m+1||R!=r+1){
		if(L!=m+1&&(R==r+1||pii(a[L][1],a[L][2])<=pii(a[R][1],a[R][2]))){
			c.modify(a[L][2],a[L][3]);
			tmp.pb(a[L]);
			L++;
		}else{
			a[R][4]+=c.query(a[R][2]);
			tmp.pb(a[R]);
			R++;
		}
	}
	rep(i,l,m+1) c.modify(a[i][2],-a[i][3]);
	rep(i,l,r+1) a[i]=tmp[i-l];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	c.resize(2e5);
	int n,k;
	cin>>n>>k;
	rep(i,1,1+n){
		cin>>a[i][0]>>a[i][1]>>a[i][2];
		a[i][3]=1;
	}
	sort(a+1,a+1+n);
	int t=1;
	rep(i,1,1+n){
		if(a[t-1][0]==a[i][0]&&a[t-1][1]==a[i][1]&&a[t-1][2]==a[i][2]){
			a[t-1][3]++;
		}else{
			a[t++]=a[i];
		}
	}
	solve(1,t-1);
	rep(i,1,t){
		ans[a[i][4]+a[i][3]]+=a[i][3];
	}
	rep(i,1,1+n){
		cout<<ans[i]<<'\n';
	}
	return 0;
}
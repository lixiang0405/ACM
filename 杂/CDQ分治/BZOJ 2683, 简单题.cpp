/*
你有一个 n×n 的棋盘，每个格子内有一个整数，初始时的时候全部为 0，现在需要维护两种操作：

1 x y A 将格子 x,y 里的数字加上 A，保证 1≤x,y≤n,1≤A≤2000。

2 x1 y1 x2 y2 输出 [x1,x2]×[y1,y2] 这个矩形内的数字和，保证 1≤x1≤x2≤n,1≤y1≤y2≤n。
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
array<int,4> a[N];

void solve(int l,int r){
	if(l==r) return;
	int m=(l+r)/2;
	solve(l,m);
	solve(m+1,r);
	int L=l,R=m+1;
	vector<array<int,4>> tmp;
	while(L!=m+1||R!=r+1){
		if(L!=m+1&&(R==r+1||pii(a[L][0],a[L][1])<=pii(a[R][0],a[R][1]))){
			if(a[L][3]==2){
				c.modify(a[L][1],a[L][2]);
			}
			tmp.pb(a[L]);
			L++;
		}else{
			if(a[R][3]==0){
				ans[a[R][2]]-=c.query(a[R][1]);
			}else if(a[R][3]==1){
				ans[a[R][2]]+=c.query(a[R][1]);
			}
			tmp.pb(a[R]);
			R++;
		}
	}
	rep(i,l,m+1){
		if(a[i][3]==2)
			c.modify(a[i][1],-a[i][2]);
	}
	rep(i,l,r+1) a[i]=tmp[i-l];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n;
	cin>>n;
	c.resize(n);
	int t=1,q=1;
	while(1){
		int ty;
		cin>>ty;
		if(ty==1){
			int x,y,A;
			cin>>x>>y>>A;
			a[t++]={x,y,A,2};
		}else if(ty==2){
			int x1,y1,x2,y2;
			cin>>x1>>y1>>x2>>y2;
			a[t++]={x2,y2,q,1};
			a[t++]={x1-1,y2,q,0};
			a[t++]={x2,y1-1,q,0};
			a[t++]={x1-1,y1-1,q,1};
			q++;
		}else break;
	}
	solve(1,t-1);
	rep(i,1,q){
		cout<<ans[i]<<'\n';
	}
	return 0;
}
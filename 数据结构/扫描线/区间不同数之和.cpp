/*有n个数a1,a2,…,an。

有q组询问，每次给一个区间[l,r]，求区间里不同的数字之和，也就是说同一个数字出现多次只算一次。*/

template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){n=s;}

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
 
    //树状数组上二分
    int ask(T s){
        int pos=0;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos+(1<<i)<=n&&c[pos+(1<<i)]<=s){
                pos+=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};

BIT<ll> tre;
int n,q;
vector<int> pos(N),a(N);
vector<pair<int,int>> que[N];
vector<ll> ans(N);

int main() {
	read(n),read(q);
	tre.resize(n);
	for(int i=1;i<=n;++i){
		read(a[i]);
	}	
	for(int i=1;i<=q;++i){
		int l,r;
		read(l),read(r);
		que[r].push_back({l,i});
	}
	for(int i=1;i<=n;++i){
		int p=pos[a[i]];
		tre.modify(p+1,a[i]);
		tre.modify(i+1,-a[i]);
		pos[a[i]]=i;
		for(auto per:que[i]){
			ans[per.second]=tre.query(per.first);
		}
	}
	for(int i=1;i<=q;++i)
	printf("%lld\n",ans[i]);
    return 0;
}

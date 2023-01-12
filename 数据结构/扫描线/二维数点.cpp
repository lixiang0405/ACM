/*平面上有n个点(xi,yi)。

回答q个询问，每个询问给定一个矩形[X1,X2]×[Y1,Y2]，询问矩形里面有多少个点。*/

#define lowbit(x) x&(-x)
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

BIT<int> tre;
int n,q;
int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&q);
	tre.resize(n);
	vector<int> ans(q+1);
	vector<array<int,4>> event;
	vector<int> vx;
	for(int i=1;i<=n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		event.push_back({y,0,x,i});
		vx.push_back(x);
	}
	stable_sort(vx.begin(),vx.end());
	vx.erase(unique(vx.begin(),vx.end()),vx.end());
	for(int i=1;i<=q;++i){
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
		event.push_back({y2,2,x2,i});
		event.push_back({y1-1,2,x1-1,i});
		event.push_back({y2,1,x1-1,i});
		event.push_back({y1-1,1,x2,i});
	}
	stable_sort(event.begin(),event.end());
	for(auto &evt:event){
		if(evt[1]==0){
			int x=lower_bound(vx.begin(),vx.end(),evt[2])-vx.begin()+1;
			tre.modify(x,1);
		}else{
			int x=upper_bound(vx.begin(),vx.end(),evt[2])-vx.begin();
			if(evt[1]==2) ans[evt[3]]+=tre.query(x);
			else ans[evt[3]]-=tre.query(x);
		}
	}
	for(int i=1;i<=q;++i){
		printf("%d\n",ans[i]);
	}
    return 0;
}

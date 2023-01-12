/*平面上有n个矩形[Xi,1,Xi,2]×[Yi,1,Yi,2]，也就是左下角(Xi,1,Yi,1)右上角(Xi,2,Yi,2)的矩形。问面积的并是多少。*/
int n;
vector<array<int,4>> event;
vector<int> vx;

struct tag{
	int add;
};

struct Tree{
	int l,r;
	int minn,cnt;
	tag t;
}tre[8*N];

void pushdon(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	b.t.add+=a.t.add;
	c.t.add+=a.t.add;
	b.minn+=a.t.add;
	c.minn+=a.t.add;
	a.t.add=0;
}

void update(int k){
	auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
	a.l=b.l,a.r=c.r;
	a.minn=min(b.minn,c.minn);
	if(b.minn==c.minn)
	a.cnt=b.cnt+c.cnt;
	else if(b.minn<c.minn)
	a.cnt=b.cnt;
	else a.cnt=c.cnt;
}

void build(int k,int x,int y){
	tre[k].t.add=0;
	if(x==y){
		tre[k]={x,x,0,vx[x]-vx[x-1]};
	}else{
		int m=(x+y)/2;
		build(k*2,x,m);
		build(k*2+1,m+1,y);
		update(k);
	}
}

void modify(int k,int x,int y,int d){
	int l=tre[k].l,r=tre[k].r;
	if(l==x&&r==y){
		tre[k].t.add+=d;
		tre[k].minn+=d;
	}else{
		if(tre[k].t.add!=0)
		pushdon(k);
		int m=(l+r)/2;
		if(y<=m) modify(k+k,x,y,d);
		else if(x>m) modify(k+k+1,x,y,d);
		else modify(k+k,x,m,d),modify(k+k+1,m+1,y,d);
		update(k);
	}
}

int main() {
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&x2,&y1,&y2);
		event.push_back({y1,1,x1,x2});
		event.push_back({y2,-1,x1,x2});
		vx.push_back(x1);
		vx.push_back(x2);
	}
	stable_sort(vx.begin(),vx.end());
	stable_sort(event.begin(),event.end());
	vx.erase(unique(vx.begin(),vx.end()),vx.end());
	int m=vx.size()-1;
	build(1,1,m);
	int tot=tre[1].cnt;
	int prey=0;
	ll ans=0;
	for(auto &cur:event){
		int x1=lower_bound(vx.begin(),vx.end(),cur[2])-vx.begin()+1;
		int x2=lower_bound(vx.begin(),vx.end(),cur[3])-vx.begin();
		if(x1>x2) continue;
		if(tre[1].minn==0)
		ans=ans+1ll*(cur[0]-prey)*(tot-tre[1].cnt);
		else ans=ans+1ll*tot*(cur[0]-prey);
		modify(1,x1,x2,cur[1]);
		prey=cur[0];
	}
	printf("%lld",ans);
    return 0;
}

/*有一个长度为n的数组 a1,a2,…,an。

你要回答q个询问，每次给一个区间[l,r]，询问这个区间内最小没有出现过的自然数。*/

struct Tree{
    int val;
}tre[4*N];

void update(int k){
    auto &a=tre[k],&b=tre[k+k],&c=tre[k+k+1];
    a.val=min(b.val,c.val);
}

void modify(int k,int l,int r,int x,int p){
    if(l==r){
        tre[k].val=p;
    }else{
        int m=(l+r)/2;
        if(x<=m) modify(k+k,l,m,x,p);
        else modify(k+k+1,m+1,r,x,p);
        update(k);
    }
}

int search(int k,int l,int r,int x){
    int m=(l+r)/2;
    if(l==r) return l;
    else if(tre[k+k].val<x) return search(k+k,l,m,x);
    else return search(k+k+1,m+1,r,x);
}

int n,q,a[N],ans[N];
vector<pair<int,int>> que[N];

int main() {
	scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i){
        int x;
        scanf("%d",&x);
        a[i]=min(x,n+1);
    }
    for(int i=1;i<=q;++i){
        int l,r;
        scanf("%d%d",&l,&r);
        que[r].push_back({l,i});
    }
    for(int r=1;r<=n;++r){
        modify(1,0,n+1,a[r],r);
        for(auto qu:que[r]){
            ans[qu.second]=search(1,0,n+1,qu.first);
        }
    }
    for(int i=1;i<=q;++i){
        printf("%d\n",ans[i]);
    }
    return 0;
}

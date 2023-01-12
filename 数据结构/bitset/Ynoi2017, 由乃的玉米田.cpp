/*
给你一个序列 a，长度为 n，有 m 次询问。
一共有三种询问，每次询问一个区间[l,r]是否可以选出两个数
（可以是同一个位置的数）使得：
1.它们的差为 x。
2.它们的和为 x。
3.它们的乘积为 x。
*/

int n,m,ans[N],tmp,c[N],cnt[N];
array<int,5> q[N];
bitset<N> s,t;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d",&c[i]);
	}
	for(int i=0;i<m;++i){
		int ty,l,r,x;
		scanf("%d%d%d%d",&ty,&l,&r,&x);
		q[i]={l,r,ty,x,i};
	}
	sort(q,q+m,[&](array<int,5> &a,array<int,5> &b){
		int x=a[0]/M,y=b[0]/M;
		if(x!=y) return x<y;
		else if(x%2) return a[1]>b[1];
		else return a[1]<b[1];
	});//先左端点按块分，再按右端点排序 偶数块从小到大，奇数块从大到小
	int l=1,r=0;
	auto add=[&](int x){
		cnt[c[x]]++;
        if(cnt[c[x]]==1) s[c[x]]=1,t[B-c[x]]=1;
	};
	auto del=[&](int x){
		cnt[c[x]]--;
        if(cnt[c[x]]==0) s[c[x]]=0,t[B-c[x]]=0;
	};
	for(int i=0;i<m;++i){
		while(q[i][1]>r) r++,add(r);
		while(q[i][0]<l) l--,add(l);
		while(q[i][1]<r) del(r),r--;
		while(q[i][0]>l) del(l),l++;
        int x=q[i][3];
		if(q[i][2]==1){
            ans[q[i][4]]=(s&(s>>x)).any();
        }else if(q[i][2]==2){
            //t=B-x s=y x+y=z -> y=z-x t=z-x+(B-z) t>>(B-z)&s即可
            ans[q[i][4]]=((t>>(B-x))&s).any();
        }else{
            for(int j=1;j*j<=x;++j){
                if(x%j==0){
                    if(s[j]&&s[x/j]){
                        ans[q[i][4]]=1;
                        break;
                    }
                }
            }
        }
	}
	for(int i=0;i<m;++i){
		puts(ans[i]?"yuno":"yumi");
	}
    return 0;
}

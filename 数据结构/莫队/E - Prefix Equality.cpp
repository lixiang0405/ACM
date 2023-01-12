/*给出了整数序列A＝（a1，…，aN）和B＝（b1，…，bN），每个长度为N。
对于i=1，…，Q，请按以下格式回答查询。
如果A（a1，…，a xi）的有一个值ai，
并且包含在B的第一yi项中的值集合（b1，…，b yi）相等，
然后打印Yes；否则，打印No.*/
//从A中从1-x的出现的值和B中从1—y出现的值一样，就yes

int n,q,a[N],b[N],vis1[2*N],vis2[2*N],ans[N];
array<int,3> que[N]; 
vector<int> vt;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	vt.clear();
	memset(vis1,0,sizeof(vis1));
	memset(vis2,0,sizeof(vis2));
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		vt.push_back(a[i]);
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
		vt.push_back(b[i]);
	}
	cin>>q;
	for(int i=1;i<=q;++i){
		cin>>que[i][0]>>que[i][1];
		que[i][2]=i;
	}
	stable_sort(vt.begin(),vt.end());
	vt.erase(unique(vt.begin(),vt.end()),vt.end());
	for(int i=1;i<=n;++i){
		a[i]=lower_bound(vt.begin(),vt.end(),a[i])-vt.begin()+1;
	}
	for(int i=1;i<=n;++i){
		b[i]=lower_bound(vt.begin(),vt.end(),b[i])-vt.begin()+1;
	}
	stable_sort(que+1,que+1+q,[&](auto &c,auto &d){
		int x=c[0]/M,y=d[0]/M;
		if(x==y){
			if(x%2==0){
				return c[1]<d[1];
			}else
			return c[1]>d[1];
		}
		else return x<y;
	});
	int l=0,r=0,cnt=0;
	auto add1=[&](int x){
		int tmp=a[x];
		vis1[tmp]++;
		if(vis1[tmp]==1&&vis2[tmp]!=0)
		cnt--;
		else if(vis1[tmp]==1&&vis2[tmp]==0)
		cnt++;
	};
	auto del1=[&](int x){
		int tmp=a[x];
		vis1[tmp]--;
		if(vis1[tmp]==0&&vis2[tmp]==0)
		cnt--;
		else if(vis1[tmp]==0&&vis2[tmp]!=0)
		cnt++;
	};
	auto add2=[&](int x){
		int tmp=b[x];
		vis2[tmp]++;
		if(vis2[tmp]==1&&vis1[tmp]!=0)
		cnt--;
		else if(vis2[tmp]==1&&vis1[tmp]==0)
		cnt++;
	};
	auto del2=[&](int x){
		int tmp=b[x];
		vis2[tmp]--;
		if(vis2[tmp]==0&&vis1[tmp]==0)
		cnt--;
		else if(vis2[tmp]==0&&vis1[tmp]!=0)
		cnt++;
	};
	for(int i=1;i<=q;++i){
		while(que[i][0]>l) l++,add1(l);
		while(que[i][0]<l) del1(l),l--;
		while(que[i][1]>r) r++,add2(r);
		while(que[i][1]<r) del2(r),r--;
		//cout<<que[i][0]<<" "<<que[i][1]<<" "<<cnt<<endl;
		ans[que[i][2]]=(cnt==0);
	}
	for(int i=1;i<=q;++i){
		if(ans[i])
		cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
    return 0;
}
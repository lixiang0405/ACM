/*
求从u到v可执行的操作
1.Turn u→u+1(modp).
2.Turn u→u+p−1(modp).
3.Turn u→up−2(modp).
求一个从u变化到v的路径
*/

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	queue<int> q,p;
	int u,v,m;
	cin>>u>>v>>m;
	if(u==v){
		cout<<0<<'\n';
		return 0;
	}
	q.push(u);
	p.push(v);
	map<int,int> a,b;
	while(1){
		int x=q.front(),y=p.front();
		q.pop();
		p.pop();
		if(b.count(x)){
			VI ans;
			int z=x;
			while(z!=u){
				if((a[z]+1)%m==z) ans.pb(1);
				else if((a[z]-1+m)%m==z) ans.pb(2);
				else ans.pb(3);
				z=a[z];
			}
			reverse(all(ans));
			z=x;
			while(z!=v){
				if((z+1)%m==b[z]) ans.pb(1);
				else if((z+m-1)%m==b[z]) ans.pb(2);
				else ans.pb(3);
				z=b[z];
			}
			cout<<SZ(ans)<<'\n';
			for(auto cur:ans){
				cout<<cur<<" ";
			}
			return 0;
		}else if(a.count(y)){
			VI ans;
			int z=y;
			while(z!=u){
				if((a[z]+1)%m==z) ans.pb(1);
				else if((a[z]-1+m)%m==z) ans.pb(2);
				else ans.pb(3);
				z=a[z];
			}
			reverse(all(ans));
			z=y;
			while(z!=v){
				if((z+1)%m==b[z]) ans.pb(1);
				else if((z+m-1)%m==b[z]) ans.pb(2);
				else ans.pb(3);
				z=b[z];
			}
			cout<<SZ(ans)<<'\n';
			for(auto cur:ans){
				cout<<cur<<" ";
			}
			return 0;
		}
		if(!a.count((x+1)%m)){
			a[(x+1)%m]=x;
			q.push((x+1)%m);
		}
		if(!a.count((x+m-1)%m)){
			a[(x+m-1)%m]=x;
			q.push((x+m-1)%m);
		}
		int f=qp(x,m-2,m);
		if(!a.count(f)){
			a[f]=x;
			q.push(f);
		}
		if(!b.count((y+1)%m)){
			b[(y+1)%m]=y;
			p.push((y+1)%m);
		}
		if(!b.count((y+m-1)%m)){
			b[(y+m-1)%m]=y;
			p.push((y+m-1)%m);
		}
		f=qp(y,m-2,m);
		if(!b.count(f)){
			b[f]=y;
			p.push(f);
		}
	}
	return 0;
}
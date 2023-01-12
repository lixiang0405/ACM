int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n,sum=0;
	cin>>n;
	for(ll l=1;l<=n;l++){
		ll d=n/l,r=n/d;
		sum+=(r-l+1)*d;
		l=r;
	}
	return 0;
}//下取整

for(int l=1;l<=b;l++){
	int d=(b+l-1)/l;
	int r;
	if(d-1){
		r=(b-1)/(d-1);
	}else r=l;
	l=r;
}//上取整

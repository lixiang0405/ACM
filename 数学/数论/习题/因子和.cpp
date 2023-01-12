ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}

ll solve(ll p,ll k,ll c){
	ll sum=1;
	if((p-1)%c==0)
	sum=sum*(k*y%c+1)%c;
	else{
		ll ans1=qp(p,k*y+1,c)%c;
		ans1=(ans1-1+c)%c;
		ll ans2=qp(p-1,c-2,c)%c;
		sum=sum*ans1%c*ans2%c;
	}
	return sum%c;
}
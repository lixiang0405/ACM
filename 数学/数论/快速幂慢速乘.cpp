ll sm(ll a,ll b,ll c){
	ll res=0;
	while(b){
		if(b&1) res=(res+a)%c;
		a=(a+a)%c;
		b>>=1;
	}
	return res;
}

ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=sm(res,a,c);
		a=sm(a,a,c);
		b>>=1;
	}
	return res;
}


ll qp(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1) res=(res*a)%c;
		a=(a*a)%c;
		b>>=1;
	}
	return res;
}
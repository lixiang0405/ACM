ll mul(ll x,ll y,ll m){
	x%=m;
	y%=m;
	ll d=(long double)x*y/m;
	d=x*y-d*m;
	if(d>=m) d-=m;
	if(d<0) d+=m;
	return d;
}
ll floordiv(ll a,ll b){
	if(a%b==0) return a/b;
	else if(a>0) return a/b;
	else return a/b-1;
}

ll ceildiv(ll a,ll b){
	if(a%b==0) return a/b;
	else if(a>0) return a/b+1;
	else return a/b;
}
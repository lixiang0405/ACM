int pri[N+5],cnt=0,eu[N+5];
bool f[N+5];
void phi(int u){
	for(int i=2;i<=u;++i){
		if(!f[i]){
			pri[cnt++]=i;
			eu[i]=i-1;
		}
		for(int j=0;j<cnt&&i*pri[j]<=u;++j){
			int per=i*pri[j];
			f[per]=true;
			if(i%pri[j]==0){
				eu[per]=eu[i]*pri[j];
				break;
			}
			eu[per]=eu[i]*(pri[j]-1);
		}
	}
}
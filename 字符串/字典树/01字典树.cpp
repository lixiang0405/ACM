const int bitmax = 31;

struct node{
	node *son[M];
	int cnt[M];
}pool[N],*cur=pool,*root,*c=pool;

node* newnode(){
	return cur++;
}

void add(ll x){
	c=root;
	per(i,0,bitmax){
		int nxt;
		if(x&(1<<i)) nxt=1;
		else nxt=0;
		if(c->son[nxt]){
			c->cnt[nxt]++;
		}
		else c->son[nxt]=newnode(),c->cnt[nxt]++;
		c=c->son[nxt];
	}
}

void del(ll x){
	c=root;
	per(i,0,bitmax){
		int nxt;
		if(x&(1<<i)) nxt=1;
		else nxt=0;
		c->cnt[nxt]--;
		c=c->son[nxt];
	}
}

ll oxrmax(ll val){
	c=root;
	per(i,0,bitmax){
		int nxt;
		if(val&(1<<i)) nxt=0;
		else nxt=1; 
		if(c->cnt[nxt]){
			val^=nxt<<i;
			c=c->son[nxt];
		}else if(c->cnt[nxt^1]){
			val^=(nxt^1)<<i;
			c=c->son[nxt^1];
		}else break;
	}
	return val;
}

ll oxrmin(ll val){
	c=root;
	per(i,0,bitmax){
		int nxt;
		if(val&(1<<i)) nxt=1;
		else nxt=0; 
		if(c->cnt[nxt]){
			val^=nxt<<i;
			c=c->son[nxt];
		}else if(c->cnt[nxt^1]){
			val^=(nxt^1)<<i;
			c=c->son[nxt^1];
		}else break;
	}
	return val;
}
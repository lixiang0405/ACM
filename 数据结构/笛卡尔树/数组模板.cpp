int stk[N],a[N],l[N],r[N];
int n;

void build(){
    int top=0;
    //for(int i=1;i<=n;++i) l[i]=r[i]=0;
    for(int i=1;i<=n;++i){
        int k=top;
        while(k>0&&a[stk[k-1]]>a[i]) --k;
        if(k) r[stk[k-1]]=i;
        if(k<top) l[i]=stk[k];
        stk[k++]=i;
        top=k;
    }
	//stk[0] is root
}
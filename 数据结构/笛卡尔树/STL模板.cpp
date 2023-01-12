int top,a[N],l[N],r[N];
int n;

void build(){
    stack<int> sk;
    int root=0;
    //for(int i=1;i<=n;++i) l[i]=r[i]=0;
    for(int i=1;i<=n;++i){
        int last=0;
        while(!sk.empty()&&a[sk.top()]>a[i]){
            last=sk.top();
            sk.pop();
        }
        if(!sk.empty()) r[sk.top()]=i;
        else root=i;
        l[i]=last;
        sk.push(i);
    }
}
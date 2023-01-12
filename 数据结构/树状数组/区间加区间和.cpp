#define lowbit(x) x&(-x)
template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){n=s;}

    T query(int x){
        assert(x<=n);
        T s=0;
        for(;x;x-=lowbit(x)){
            s+=c[x];
        }
        return s;
    }

    void modify(int x,T s){
        assert(x!=0);
        for(;x<=n;x+=lowbit(x)){
            c[x]+=s;
        }
    }
 
    //树状数组上二分
    int ask(T s){
        int pos=0;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos+(1<<i)<=n&&c[pos+(1<<i)]<=s){
                pos+=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};

BIT<ull> c,d;

//令所有的ai(l≤i≤r)加上d。
void modify(int l,int r,ll f){
    c.modify(l,f);
    c.modify(r+1,-f);
    d.modify(l,f*l);
    d.modify(r+1,-f*(r+1));
}

//查询(∑(i=1-x)ai)
ll query(int l,int r){
    l--;
    return c.query(r)*(r+1)-d.query(r)-c.query(l)*(l+1)+d.query(l);
}
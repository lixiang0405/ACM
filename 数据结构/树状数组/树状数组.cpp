#define lowbit(x) x&(-x)
template<class T>
struct BIT{
    T c[N];
    int n;
    void resize(int s){
        n=s;
        for(int i=1;i<=n;++i) c[i]=0;
    }

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
 
    //树状数组上二分 查询最大的T(0≤T≤n)满足∑(i=1-T) ai≤s。
    int ask(T s){
        int pos=n;
        for(int i=18;i>=0;--i) //i=18:2的i次方>=n
            if(pos-(1<<i)<=n&&c[pos-(1<<i)]<=s){
                pos-=(1<<i);
                s-=c[pos];
            }
        return pos;
    }
};
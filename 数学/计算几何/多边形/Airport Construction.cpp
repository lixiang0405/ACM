/*
皮科尼西亚这个热带岛国以其美丽的海滩、茂密的植被、
可可和咖啡种植园以及全年宜人的天气而闻名。
这个天堂被认为是未来 ACM 国际大学编程竞赛世界总决赛的地点
（或者至少是执行委员会的度假胜地）。
只有一个小问题：这个岛真的很难到达。
目前，从最近的机场到岛上最快的方式是三天，
并且使用渔船、油轮、皮划艇和潜艇的组合。
为了更轻松地参加 ICPC 世界总决赛并启动岛上的旅游业务，
皮科尼西亚正计划建造其第一个机场。
由于更长的着陆跑道可以容纳更大的飞机，
皮科尼西亚决定在他们的岛上建造尽可能长的着陆跑道。
不幸的是，他们无法确定该着陆带应该位于何处。
也许你能帮忙？
对于这个问题，我们将 Piconesia 的边界建模为一个多边形。
给定这个多边形，您需要计算可以在岛上建造的最长着陆带（即直线段）的长度。
着陆带不得与海相交，但可以接触或沿着岛屿边界延伸。
*/

typedef double db;
const db EPS = 1e-9;
  
inline int sign(db a) { return a < -EPS ? -1 : a > EPS; }
  
inline int cmp(db a, db b){ return sign(a-b); }
  
struct P {
    db x, y;
    P() {}
    P(db _x, db _y) : x(_x), y(_y) {}
    P operator+(P p) { return {x + p.x, y + p.y}; }
    P operator-(P p) { return {x - p.x, y - p.y}; }
    P operator*(db d) { return {x * d, y * d}; }
    P operator/(db d) { return {x / d, y / d}; }
 
    bool operator<(P p) const { 
        int c = cmp(x, p.x);
        if (c) return c == -1;
        return cmp(y, p.y) == -1;
    }
 
    bool operator==(P o) const{
        return cmp(x,o.x) == 0 && cmp(y,o.y) == 0;
    }
 
    db dot(P p) { return x * p.x + y * p.y; }//点积
    db det(P p) { return x * p.y - y * p.x; }//叉积
     
    db distTo(P p) { return (*this-p).abs(); }//两点之间的距离
    db alpha() { return atan2(y, x); }//求极交角：正半轴转多少°到该点   [-pi,pi]
    void read() { cin>>x>>y; }
    void write() {cout<<"("<<x<<","<<y<<")"<<endl;}
    db abs() { return sqrt(abs2());}
    db abs2() { return x * x + y * y; }
    P rot90() { return P(-y,x);}//逆时针转90°
    P unit() { return *this/abs(); }//方向向量
    //极角在上半轴还是在下半轴
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
    P rot(db an){ return {x*cos(an)-y*sin(an),x*sin(an) + y*cos(an)}; }//转一个角度an
};
 
#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y)) //三个点p1p2 X p1p3
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3)) //=0 三点共线 <0 p1p2p3顺时针方向

//求直线的交点
P isLL(P p1, P p2, P q1, P q2) { 
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}
  
//m 在 a和b 之间
bool isMiddle(db a, db m, db b) {
    return sign(a - m) == 0 || sign(b - m) == 0 || (a < m != b < m);
}

//点m是不是横纵都在a和b之间  
bool isMiddle(P a, P m, P b) {
    return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}

//点p在线段p1p2上
bool onSeg(P p1, P p2, P q){
    return crossOp(p1,p2,q) == 0 && isMiddle(p1, q, p2);
}

//面积  
db area(vector<P> ps){
    db ret = 0; rep(i,0,ps.size()) ret += ps[i].det(ps[(i+1)%ps.size()]); 
    return ret/2;
}
//点包含
int contain(vector<P> ps, P p){ //2:inside,1:on_seg,0:outside
    int n = ps.size(), ret = 0; 
    rep(i,0,n){
        P u=ps[i],v=ps[(i+1)%n];
        if(onSeg(u,v,p)) return 1;
        if(cmp(u.y,v.y)<=0) swap(u,v);
        if(cmp(p.y,u.y) >0 || cmp(p.y,v.y) <= 0) continue;
        ret ^= crossOp(p,u,v) > 0;
    }
    return ret*2;
}
//严格凸包
vector<P> convexHull(vector<P> ps) {
    int n = ps.size(); if(n <= 1) return ps;
    sort(ps.begin(), ps.end());
    vector<P> qs(n * 2); int k = 0;
    for (int i = 0; i < n; qs[k++] = ps[i++]) 
        while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
    for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
        while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) <= 0) --k;
    qs.resize(k - 1);
    return qs;
}
//不严格凸包  
vector<P> convexHullNonStrict(vector<P> ps) {
    //caution: need to unique the Ps first
    int n = ps.size(); if(n <= 1) return ps;
    sort(ps.begin(), ps.end());
    vector<P> qs(n * 2); int k = 0;
    for (int i = 0; i < n; qs[k++] = ps[i++]) 
        while (k > 1 && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
    for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
        while (k > t && crossOp(qs[k - 2], qs[k - 1], ps[i]) < 0) --k;
    qs.resize(k - 1);
    return qs;
}
//旋转卡壳  
db convexDiameter(vector<P> ps){
    int n = ps.size(); if(n <= 1) return 0;
    int is = 0, js = 0; rep(k,1,n) is = ps[k]<ps[is]?k:is, js = ps[js] < ps[k]?k:js;
    int i = is, j = js;
    db ret = ps[i].distTo(ps[j]);
    do{
        if((ps[(i+1)%n]-ps[i]).det(ps[(j+1)%n]-ps[j]) >= 0)
            (++j)%=n;
        else
            (++i)%=n;
        ret = max(ret,ps[i].distTo(ps[j]));
    }while(i!=is || j!=js);
    return ret;
}
//切多边形
vector<P> convexCut(const vector<P>&ps, P q1, P q2) {
    vector<P> qs;
    int n = ps.size();
    rep(i,0,n){
        P p1 = ps[i], p2 = ps[(i+1)%n];
        int d1 = crossOp(q1,q2,p1), d2 = crossOp(q1,q2,p2);
        if(d1 >= 0) qs.pb(p1);
        if(d1 * d2 < 0) qs.pb(isLL(p1,p2,q1,q2));
    }
    return qs;
}

bool isSS_strict(P p1, P p2, P q1, P q2){
    return crossOp(p1,p2,q1) * crossOp(p1,p2,q2) < 0;//注意：这里只要判线段无限延长相不相交
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d",&n);
    vector<P> p(n);
    rep(i,0,n){
        scanf("%lf%lf",&p[i].x,&p[i].y);
    }
    db ans=0;
    rep(i,0,n) rep(j,i+1,n){
        vector<P> d;
        rep(k,0,n)
            if(crossOp(p[i],p[j],p[k])==0) d.pb(p[k]);
            else if(isSS_strict(p[i],p[j],p[k],p[(k+1)%n])) d.pb(isLL(p[i],p[j],p[k],p[(k+1)%n]));
        sort(all(d));
        d.erase(unique(all(d)),d.end());
        int m=SZ(d);
        if(d[0].distTo(d[m-1])<ans) continue;
        int a,b;
        rep(k,0,m) 
            if(d[k]==p[i]) a=k;
            else if(d[k]==p[j]) b=k;
        bool flag=true;
        db res=0;
        if(a>b) swap(a,b);
        rep(k,a,b){
            if(!contain(p,(d[k]+d[k+1])/2)){
                flag=false;
                break;
            }else{
                res+=d[k].distTo(d[k+1]);
            }
        }
        if(!flag) continue;
        per(k,0,a)
            if(contain(p,(d[k]+d[k+1])/2)) res+=d[k].distTo(d[k+1]);
            else break;
        rep(k,b,m-1) 
            if(contain(p,(d[k]+d[k+1])/2)) res+=d[k].distTo(d[k+1]);
            else break;
        ans=max(ans,res);
    }
    printf("%.10lf",ans);
    return 0;
} 
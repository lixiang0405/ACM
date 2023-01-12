/*
今天，首届自动驾驶大赛正式开始！
本次比赛的实验场地是二维平面上的一个矩形区域，坐标轴与坐标轴平行。
字段的左下角位于坐标 (xl,yl)，而右上角位于坐标 (xr,yr)。
有两个线段 A 和 B 严格位于矩形内。
这两个部分可能有共同点。
矩形里面还有一辆车，可以看成一个点。
本次比赛的一个子任务要求在运动过程中，汽车与两段之间的距离必须始终相等。
点 P 和线段 Q 之间的距离定义为 P 到 Q 上任意点的最小欧几里得距离。
请编写一个程序来查找汽车有效位置的区域。
*/

//求一个区域内到两条线段距离相等的点的面积

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

int t;

void solve(){
    vector<P> rect(4);
    rect[0].read();
    rect[2].read();
    rect[1]=P(rect[2].x,rect[0].y);
    rect[3]=P(rect[0].x,rect[2].y);
    vector<P> p(2),q(2);
    p[0].read();
    p[1].read();
    q[0].read();
    q[1].read();
    db ans=0;
    rep(i,0,2) rep(j,0,2)
        if(p[i]==q[j]){
            auto r=convexCut(rect,p[i],p[i]+(p[1-i]-p[i]).rot90());
            r=convexCut(r,q[j],q[j]+(q[1-j]-q[j]).rot90());
            ans+=area(r);
        }
    if(crossOp(p[0],q[0],q[1])==0&&crossOp(p[1],q[0],q[1])==0){
        auto r=rect;
        rep(i,0,2)
            r=convexCut(r,p[i],p[i]+(p[i]-p[1-i]).rot90());
        rep(i,0,2)
            r=convexCut(r,q[i],q[i]+(q[i]-q[1-i]).rot90());
        ans+=area(r);
    }
    cout<<fixed<<setprecision(10)<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
} 
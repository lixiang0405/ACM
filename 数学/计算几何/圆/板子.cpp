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

const db PI = 4*atanl(1);
//圆和原的关系
int type(P o1,db r1,P o2,db r2){
    db d = o1.distTo(o2);
    if(cmp(d,r1+r2) == 1) return 4;
    if(cmp(d,r1+r2) == 0) return 3;
    if(cmp(d,abs(r1-r2)) == 1) return 2;
    if(cmp(d,abs(r1-r2)) == 0) return 1;
    return 0;
}

//圆和线相交
vector<P> isCL(P o,db r,P p1,P p2){
    if (cmp(abs((o-p1).det(p2-p1)/p1.distTo(p2)),r)>0) return {};
    db x = (p1-o).dot(p2-p1), y = (p2-p1).abs2(), d = x * x - y * ((p1-o).abs2() - r*r);
    d = max(d,(db)0.0); P m = p1 - (p2-p1)*(x/y), dr = (p2-p1)*(sqrt(d)/y);
    return {m-dr,m+dr}; //along dir: p1->p2
}
  
//圆和圆相交
vector<P> isCC(P o1, db r1, P o2, db r2) { //need to check whether two circles are the same
    db d = o1.distTo(o2); 
    if (cmp(d, r1 + r2) == 1) return {};
    if (cmp(d,abs(r1-r2))==-1) return {};
    d = min(d, r1 + r2);
    db y = (r1 * r1 + d * d - r2 * r2) / (2 * d), x = sqrt(r1 * r1 - y * y);
    P dr = (o2 - o1).unit();
    P q1 = o1 + dr * y, q2 = dr.rot90() * x;
    return {q1-q2,q1+q2};//along circle 1第一个圆逆时针方向
}
  
// (外公切线)extanCC,(内公切线)intanCC:-r2,(点到圆的切线)tanCP:r2=0
vector<pair<P, P>> tanCC(P o1, db r1, P o2, db r2) {
    P d = o2 - o1;
    db dr = r1 - r2, d2 = d.abs2(), h2 = d2 - dr * dr;
    if(sign(d2) == 0 || sign(h2) < 0) return {};
    h2 = max((db)0.0, h2);
    vector<pair<P, P>> ret;
    for(db sign : {-1, 1}) {
        P v = (d * dr +d.rot90() * sqrt(h2) *sign) / d2;
        ret.push_back({o1 + v*r1, o2 + v*r2});
    }
    if(sign(h2) == 0) ret.pop_back();
    return ret;
}

//内心
P inCenter(P A, P B, P C) {
    double a = (B - C).abs(), b = (C - A).abs(), c = (A - B).abs();
    return (A * a + B * b + C * c) / (a + b + c);
}

//外心 
P circumCenter(P a, P b, P c) { 
    P bb = b - a, cc = c - a;
    double db = bb.abs2(), dc = cc.abs2(), d = 2 * bb.det(cc);
    return a - P(bb.y * dc - cc.y * db, cc.x * db - bb.x * dc) / d;
}
 
//垂心 
P othroCenter(P a, P b, P c) { 
    P ba = b - a, ca = c - a, bc = b - c;
    double Y = ba.y * ca.y * bc.y,
    A = ca.x * ba.y - ba.x * ca.y,
    x0 = (Y + ca.x * ba.y * b.x - ba.x * ca.y * c.x) / A,
    y0 = -ba.x * (x0 - c.x) / ba.y + ca.y;
    return {x0, y0};
}

//最小圆覆盖(O(n))
pair<P, db> min_circle(vector<P> ps) {
    random_shuffle(ps.begin(), ps.end());
    int n = ps.size();
    P o = ps[0];
    db r = 0;
    rep(i,1,n) if(o.distTo(ps[i]) > r + EPS){
        o = ps[i], r = 0;
        rep(j,0,i) if(o.distTo(ps[j]) > r + EPS){
            o = (ps[i] + ps[j]) / 2; 
            r = o.distTo(ps[i]);
            rep(k,0,j) if(o.distTo(ps[k]) > r + EPS){
                o = circumCenter(ps[i], ps[j], ps[k]);
                r = o.distTo(ps[i]); 
            }
        }
    }
    return {o, r};
}

//两个向量之间的theta
db rad(P p1,P p2){
    return atan2l(p1.det(p2),p1.dot(p2));
}

//圆与简单多边形面积交
db areaCT(db r, P p1, P p2){
    vector<P> is = isCL(P(0,0),r,p1,p2);
    if(is.empty()) return r*r*rad(p1,p2)/2;
    bool b1 = cmp(p1.abs2(),r*r) == 1, b2 = cmp(p2.abs2(), r*r) == 1;
    if(b1 && b2){
        if(sign((p1-is[0]).dot(p2-is[0])) <= 0 &&
            sign((p1-is[1]).dot(p2-is[1])) <= 0)
        return r*r*(rad(p1,is[0]) + rad(is[1],p2))/2 + is[0].det(is[1])/2;
        else return r*r*rad(p1,p2)/2;
    }
    if(b1) return (r*r*rad(p1,is[0]) + is[0].det(p2))/2;
    if(b2) return (p1.det(is[1]) + r*r*rad(is[1],p2))/2;
    return p1.det(p2)/2;
}

//圆的面积并
db intergal(db x,db y,db r,db L,db R){
    return r*r*(R-L) + x*r*(sinl(R) - sinl(L)) + y*r*(-cosl(R) + cosl(L));
}

db calc_area_circle(P c,db r,db L,db R){
    return intergal(c.x,c.y,r,L,R) / 2;
}

db norm(db x){
    while(x < 0) x += 2 * PI;
    while(x > 2 * PI) x -= 2* PI;
    return x;
}

P cs[N];
db rs[N];
//圆的面积并
db areaCC(P O,int m){
    vector<int> cand = {};
    rep(i,0,m){
        bool ok = 1;
        rep(j,0,m) if(i!=j){
            if(rs[j] > rs[i] + EPS && rs[i] + cs[i].distTo(cs[j]) <= rs[j] + EPS){
                ok = 0;
                break;
            }
            if(cs[i] == cs[j] && cmp(rs[i],rs[j]) == 0 && j < i){
                ok = 0;
                break;
            }
        }
        if(ok) cand.pb(i);
    }
    rep(i,0,SZ(cand)) cs[i] = cs[cand[i]], rs[i] = rs[cand[i]];
    m = cand.size();
    db area = 0;
    P wc = O;
    rep(i,0,m){
        vector<pair<db,int>> ev = {{0, 0},{2 * PI, 0}};
        int cur = 0;
        rep(j,0,m) if(j!=i){
            auto ret = isCC(cs[i],rs[i],cs[j],rs[j]);
            if(!ret.empty()){
                db l = (ret[0] - cs[i]).alpha();
                db r = (ret[1] - cs[i]).alpha();
                l = norm(l);
                r = norm(r);
                ev.pb({l, 1});
                ev.pb({r, -1});
                if(l > r) ++cur;
            }
        }
        sort(ev.begin(),ev.end());
        rep(j,0,SZ(ev)-1){
            cur += ev[j].se;
            if(cur == 0){
                area += calc_area_circle(cs[i],rs[i],ev[j].fi,ev[j+1].fi);
            }
        }   
    }
    return area;
}

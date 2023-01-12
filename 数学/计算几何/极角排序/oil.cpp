/*ICPC 目前关注分层存款。
为了简化分析，ICPC 仅考虑二维情况，其中油藏被建模为平行于地球表面的水平线段。
ICPC 想知道如何放置一口油井以提取最大量的石油。
油井是从地面沿直线钻出的，并且可以从其向下相交的所有沉积物中提取石油，
即使相交处位于沉积物的端点处也是如此。
在这个简单的模型中，沉积物中所含的油量等于沉积物的宽度。
你能帮助ICPC确定单口井可以提取的最大石油量吗？*/

typedef long long db;
const db EPS = 0;
  
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

//两条直线是否相交
bool chkLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1+a2) != 0;
}

//求直线的交点
P isLL(P p1, P p2, P q1, P q2) { 
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}
  
//判断 区间 [l1,r1],[l2,r2] 是否相交(l1,r1)大小无所谓
bool intersect(db l1,db r1,db l2,db r2){
    if(l1>r1) swap(l1,r1); if(l2>r2) swap(l2,r2); 
    return !( cmp(r1,l2) == -1 || cmp(r2,l1) == -1 );
}

//线段相交
bool isSS(P p1, P p2, P q1, P q2){
    return intersect(p1.x,p2.x,q1.x,q2.x) && intersect(p1.y,p2.y,q1.y,q2.y) && 
    crossOp(p1,p2,q1) * crossOp(p1,p2,q2) <= 0 && crossOp(q1,q2,p1)
            * crossOp(q1,q2,p2) <= 0;
}
  
//线段严格相交(不能交到端点且有且只能有一个交点) 
bool isSS_strict(P p1, P p2, P q1, P q2){
    return crossOp(p1,p2,q1) * crossOp(p1,p2,q2) < 0 && crossOp(q1,q2,p1)
            * crossOp(q1,q2,p2) < 0;
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
 
//点q严格在p1p2上(不包含端点)
bool onSeg_strict(P p1, P p2, P q){
    return crossOp(p1,p2,q) == 0 && sign((q-p1).dot(p1-p2)) * sign((q-p2).dot(p1-p2)) < 0;
}
  
//求q到直线p1p2的投影(垂足)：p1!=p2
P proj(P p1, P p2, P q) {
    P dir = p2 - p1;
    return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}
  
//求q以直线p1p2为轴的反射  
P reflect(P p1, P p2, P q){
    return proj(p1,p2,q) * 2 - q;
}

//求q到线段p1p2的最小距离
db nearest(P p1,P p2,P q){
    if (p1==p2) return p1.distTo(q);
    P h = proj(p1,p2,q);
    if(isMiddle(p1,h,p2))
        return q.distTo(h);
    return min(p1.distTo(q),p2.distTo(q));
}

//求线段p1p2与线段q1q2的距离
db disSS(P p1, P p2, P q1, P q2){
    if(isSS(p1,p2,q1,q2)) return 0;
    return min(min(nearest(p1,p2,q1),nearest(p1,p2,q2)), min(nearest(q1,q2,p1),nearest(q1,q2,p2)));
}

//极角排序
/*
    sort(p,p+n,[&](const P &a, const P &b) {
        int qa = a.quad(), qb = b.quad();
        if(qa != qb) return qa < qb;
        else return sign(a.det(b)) > 0;
    });
*/

int n;
P p[N][2];

ll solve(P o){
    vector<pair<P,int>> evt; 
    rep(i,1,n+1){
        P a=p[i][0]-o,b=p[i][1]-o;
        int w=b.x-a.x;
        if(a.y<0){
            evt.pb({a*(-1),w});
            evt.pb({b*(-1),-w});
        }else if(a.y>0){
            evt.pb({b,w});
            evt.pb({a,-w});
        }
    }
    sort(all(evt),[&](pair<P,int> &a,pair<P,int> &b){
        auto d=a.fi.det(b.fi);
        if(d!=0) return d>0;
        else return a.se>b.se;
    });
    ll ans=0,tot=0;
    for(auto cur:evt){
        tot+=cur.se;
        ans=max(ans,tot);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	scanf("%d",&n);
	rep(i,1,n+1){
		int x1,x2,y;
		scanf("%d%d%d",&x1,&x2,&y);
		if(x1>x2) swap(x1,x2);
		p[i][0]=P(x1,y),p[i][1]=P(x2,y); 
	}
	ll ans=0;
	rep(i,1,n+1){
		ans=max(ans,max(solve(p[i][0]),solve(p[i][1])+p[i][1].x-p[i][0].x));
	}
	printf("%lld",ans);
	return 0;
} 
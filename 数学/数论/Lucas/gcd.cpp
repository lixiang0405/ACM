ll gcd(ll x,ll y){
    return y==0?x:gcd(y,x%y);
}
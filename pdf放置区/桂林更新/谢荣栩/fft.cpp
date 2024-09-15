const int N=1e6+10;
const long double Pi=acos(-1);
int n,m,limit;
int l, r[1<<20];

const int EX = 20;
const long double pi = 3.1415926535897932384626433832795028841971;
// Complex number
pair<long double, long double> operator+(const pair<long double, long double> &a, const pair<long double, long double> &b) {
    return {a.x + b.x, a.y + b.y};
}
pair<long double, long double> operator-(const pair<long double, long double> &a, const pair<long double, long double> &b) {
    return {a.x - b.x, a.y - b.y};
}
pair<long double, long double> operator*(const pair<long double, long double> &a, const pair<long double, long double> &b) {
    return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}
void FFT(pair<long double, long double> *a,int op){
    for(int i=0; i<limit; i++){
        if(i<r[i]) swap(a[i],a[r[i]]);
    }
    for(int mid=1; mid<limit; mid<<=1){
        pair<long double, long double> W(cos(Pi/mid),op*sin(Pi/mid));
        for(int r=mid<<1,j=0; j<limit; j+=r){
            pair<long double, long double> w(1,0);
            for(int l=0; l<mid; l++,w=w*W){
                pair<long double, long double> x=a[j+l],y=w*a[j+mid+l];
                a[j+l]=x+y; a[j+mid+l]=x-y;
            }
        }
    }
}

vector<int> operator*(const vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size();
    vector<int> ans(n + m - 1);
    n--, m--;
    limit = 1;
    l = 0;
    while (limit <= n + m)
        limit <<= 1, l++;
    for (int i = 1; i <= limit; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    pair<long double, long double> *c = new pair<long double, long double>[limit]();
    for (int i = 0; i <= n; i++)
        c[i].x = a[i];
    for (int i = 0; i <= m; i++)
        c[i].y = b[i];
    FFT(c, 1);
    for (int i = 0; i < limit; i++)
        c[i] = c[i] * c[i];
    FFT(c, -1);
    for (int i = 0; i <= n + m; i++)
        ans[i] = c[i].y / (limit << 1) + 0.5;
    delete[] c;
    return ans;
}